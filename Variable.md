#### Variable

##### variable substitution

变量仅在定义、赋值、unset、export、在双括号 (( ... )) 内的算术表达式中，或在表示信号的变量的特殊情况下不含$前缀。

两种引用

- partial quoting, or weak quoting  双引号中不影响变量替换

- full quoting  单引号中变量名会被按字面量使用，不发生变量替换

```shell
#!/bin/bash
# 赋值时等号两侧不允许有空格
# "VARIABLE =value"    脚本尝试运行带有"=value"参数的命令VARIABLE
# "VARIABLW= value"    脚本尝试运行value指令，且环境变量VARIABLE set to ""

hello="A B  C   D"
echo $hello    # A B C D
echo "$hello"  # A B  C   D
echo '$hello'  # $hello
```

注意变量设为空值和不设置它有区别。

```shell
# 未初始化的变量有一个空值，在算术操作中被视作零
unset uninitialized_variable
echo "uninitialized_variable = $uninitialized_variable"
# uninitialized_variable = 

# ---------------------------------------------------------

if [ -z "$unassigned" ]
then
    echo "\$unassigned is NULL"
fi    # $unassigned is NULL
```

##### variable assignment

`=`赋值

let 赋值    `let a=16+5`

for 循环中变量赋值

```shell
for a in 7 8 9 11
do
    echo -n "$a "
done
```

在read语句中（也是一种赋值）

```bash
echo -n "Enter \"a\" "
read a
echo "The value of \"a\" is now $a."
```

使用$(...)机制变量赋值

```shell
# From /etc/rc.d/rc.local
R=$(cat /etc/redhat-release)
arch=$(uname -m)
```

> Bash变量是无类型的，本质上是字符串，允许仅包含数字的变量进行算术运算和比较。

```shell
a=2334
b=${a/23/BB}
echo "b = $b"    # BB34
```

##### special variable types

- Local variables 局部变量变量仅在代码块或函数中可见。局部变量有局部范围。与C相反，仅当函数中的bash变量被声明为local时才为局部变量。
  
  ```shell
  func ()
  {
      local loc_var=23    # 声明为local变量
      echo
      global_var=999    # 没有声明为local变量，默认为global
  }
  echo "\"loc_var\" outside function = $loc_var"
  # "loc_var" outside function = 
  echo "\"global_var\" outside function = $global_var"
  # "global_var" outside function = 999
  # 函数调用前，所有在函数中声明的变量的对外都是不可见的，不只是local变量
  ```
  
  
  

- Environmental variables 环境变量
  
  影响shell和用户界面行为的变量。一般而言，每个进程都有一个环境，即进程可能引用的一组变量。从这个意义上说，shell的行为与任何其他进程一样。每次shell启动时，它都会创建与自己的环境变量相对应的shell变量。更新或添加新的环境变量会导致shell更新其环境，并且shell的所有子进程（它所执行的命令）都会继承此环境。
  
  > 分配给环境的空间是有限的。创建太多环境变量或使用过多空间的环境变量可能会导致问题。
  
  如果脚本设置了环境变量，则需要export它们。即报告给脚本本地的环境。
  
  脚本只能将变量导出到子进程，即只能导出到该特定脚本启动的命令或进程。从命令行调用的脚本无法将变量导出回命令行环境。子进程不能将变量导出回产生它们的父进程。

- Positional parameters
  
  从命令行传递给脚本的参数：`$0, $1, $2, $3...`
  
  $0是脚本名字，\$1是第一个参数，以此类推。
  
  \$* 和 \$@ 代表所有位置参数。两者必须被双引起来，即"\$*", "\$@"
  
  而两者的区别是$@，每个参数都是一个带引号的字符串，即参数原封不动地传递，没有解释或扩展，参数列表中的每个参数都被视为一个单独的词。
  
  ```shell
  index=1
  for arg in "$*"
  do
      echo "Arg #$index = $arg"
      let "index+=1"
  done
  echo "Entire arg list seen as single word."
  
  echo
  
  index=1
  for arg in "$@"
  do
      echo "Arg #$index = $arg"
      let "index+=1"
  done
  echo "Arg list seen as separate words."
  ```

```shell
TIMEOUT=30
count=0
possibly_hanging_job & {
while ((count < TIMEOUT )); do
    eval '[ ! -d "/proc/$lastjob" ] && ((count = TIMEOUT))'
    lastjob=$!
    ((count++))
    sleep 1
done
eval '[ -d "/proc/$lastjob" ] && kill -15 &lastjob'
}
```

- `$_`
  
  设置为先前执行命令的最终参数的特殊变量。
  
  ```shell
  #!/bin/bash
  
  echo $_    # /bin/bash
             # Just called /bin/bash to run the script
  # Note that this will vary according to how the script is invoked
  du >/dev/null
  echo $_    # du
  
  ls -al >/dev/null    # So no output from command
  echo $_    # -al (last argument)
  
  :
  echo $_    # :
  ```

- `$?`
  
  命令/函数/脚本本身的退出状态，

- `$$`
  
  脚本本身的进程ID
  
  常用来创建唯一临时文件
  
  ```shell
  TEMPFILE=temp.$$
  # Create a "unique" temp file name, using process id of the script
  # Using 'mktemp' is an alternative
  # For example: TEMPFILE=`mktemp temp.XXXXXX`
  ```
  
  ```shell
  MINPARAMS=10
  if [ $# -lt "$MINPARAMS" ]
  then
      echo
      echo "This script needs at $MINPARAMS command-line arguments!"
  fi
  
  args=$#
  lastarg=${!args}    # last argument
  # Or lastarg=${!#}
  ```

`shift`命令重排位置参数，`$1 <--- $2, $2 <--- $3, $3 <--- $4, etc`。旧的\$1消失，而\$0不变，仍为脚本名。
