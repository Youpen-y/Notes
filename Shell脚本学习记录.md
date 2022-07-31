### Shell 脚本

#### sha-bang

`#!` sha-bang，标识文件类型的特定标记，实际上是一个两字节的magic number。sha-bang + 解释器路径

> she-bang or sh-bang, 来源是sharp(#) 和 bang(!)的结合
> 
> 一些 UNIX 风格（基于 4.2 BSD 的）据称采用四字节幻数，在 ! 之后需要一个空格。  `--#！ /bin/sh`。

```bash
# 调用不同的命令解释器
#!/bin/sh       (UNIX默认Bourne shell)
#!/bin/bash    （Linux系统默认)
#!/usr/bin/perl
#!/usr/bin/tcl
#!/bin/sed -f
#!/bin/awk -f
```

如果脚本仅包含一组通用系统命令，不使用内部shell指令，`#！`则可以省略。

```bash
#!/bin/rm        # 解释时将成为 /bin/rm filename
# 文件名成为#！后指定程序的参数
```

> 注意：sha-bang后的路径必须正确，否则产生错误"Command not found"
> 
> 有时bash不在/bin中，可通过`#!/bin/env bash`避免该错误。

#### 脚本调用

`sh scriptname`缺陷：关闭Bash特定的扩展，脚本可能无法执行。

`sh <scriptname` 缺陷：关闭了脚本内从stdin读取输入的功能。

`bash scriptname`

更方便的是先授权，后执行

`chmod 555 scriptname`    给每个人读取或执行权限

`chmod +rx scriptname`    与上式等价

`chmod u+rx scriptname `    只给脚本所有者读或执行权限

通过`./scriptname`执行

> 如果位于脚本当前所在目录，为何不能通过scriptname调用脚本？
> 
> 因为安全的原因，`./`没有默认包含在用户\$PATH环境变量中。因此需要显示调用脚本。将脚本加入`/usr/local/bin/`后可通过scriptname调用脚本。

#### 参数替换（Parameter substitution）

```bash
#!/bin/bash4

var=veryMixedUpVariable
echo ${var}        # veryMixedUpVariable
echo ${var^}       # VeryMixedUpVariable (首字符大写)
echo ${var^^}      # VERYMIXEDUPVARIABLE (所有字符大写)

echo ${var,}       # veryMixedUpVariable (首字符小写)
echo ${var,,}      # verymixedupvariable (所有字符小写)
```

##### Command substitution

\`command\` 结构使该命令的输出可以复制给一个变量。

```bash
script_name=`basename $0`
echo "The name of this script is $script_name."
```

#### 空指令（null command, :)

```bash
# ":" 是shell中NOP的等价物，（no op, do-nothing operation）
# ":" 命令本身是Bash内置命令，它的退出状态是真（0）
：
echo $?    # 0
------------------
# endless loop
while :
do
    operation-1
    operation-2
    ...
    operation-3
done

# Same as:
    while true
    do
      ...
    done
```

#### Placeholder in if/then test

```bash
if condition
then :    # Do nothing and branch ahead
else
    take-some-action
fi
```

#### set

`set` 命令是一个内置的 Linux shell 命令，用于显示和设置 shell 和 Linux 环境变量的名称和值。（常用于调试脚本）

```bash
set [options] [arguments]
```

`[options]` 是在 Bash shell 环境中设置或取消设置的设置或标志。使用它来影响已定义的 shell 脚本的行为并帮助执行所需的任务。

- 设置一个option使用 `-options` 

- 取消设置一个option使用 `+options`

`[arguments]` 是位置参数，它们使用以下参数按顺序分配：`$1`, `$2`...

不指定任何选项或参数会导致该命令打印所有 shell 变量。

set 命令具有三个退出值：

- 0 标志着成功完成。

- 1 参数无效导致的失败。

- 2 失败导致使用消息，通常是因为缺少参数。

| Options | -o flags   | Description             |
| ------- | ---------- | ----------------------- |
| -e      | -o errexit | 脚本出错（命令返回非0值），shell立即退出 |
| +e      |            | 默认状态，（命令返回非0，依旧执行）      |
| -x      | -o xtrace  | 在执行中打印命令参数              |

###### 通配符wildcard

> Using wildcards to get all the results that fits a certain pattern is precisely what we call globbing.

`*`:    零个或多个字符

`?`:    一个字符

#### 字符扩展

`$#`:    命令行参数总数，不含\$0

`$*`, `$@`:    用来展示所有命令行参数，不含\$0

- 区别：当包括在双引号中时，`$*`扩展为`$1c$2c$3c...`，c是$IFS的首字符，bash 内部字段分隔符变量，IFS用来字符分隔，默认值为“空格, tab, 或换行"。
  
  ```bash
  set -- one two "three four"
  # Everything after set -- is registered as a positional parameter
  for arg in $@; do echo "$arg"; done
  IFS=","; for arg in "$*"; do echo "$arg"; done
  ```

`$0`:    脚本或程序名

`shift`:    将命令行参数左移一个位置，第一个参数丢失。

`shift n`:    将命令行参数左移n个位置    

#### Bash 大括号`{}`的使用

#### Bash 方括号`[]`的使用

- 方括号是执行条件测试的简写符号。括号`[`和`[[`是 Unix 中的实际命令。在Bash中，`[`是内置命令，可执行文件==test，`[[`是Bash的关键字。
  
  ```bash
  $ type -a [
  [ is a shell builtin
  [ is /usr/bin/[
  [ is /bin/[
  
  $ type -a [[
  [[ is a shell keyword
  ```
  
  $ [ -f file ]    # 测试文件file是否存在
  
  $ [ ! -f file ]  # 测试文件file是否不存在
  
  $ [ -d dir ]     # 是否是目录
  
  $ [ -r  "\$1" ]    # $1是否可读
  
  $ [ -w  "\$1" ]    # $1是否可写
  
  $ [ -e  "\$1" ]    # $1是否存在

```
```bash
test expr
== [ expr ]
    根据条件表达式 expr 返回0或1。
```

  `if` is part of a conditional, `test` or `[ ... ]` command simply evaluate the conditional, and return a 0 or a 1. The 0 or 1 is then acted on by the if statement.

```bash
if [ ... ]; then
    ... do this ...
else
    ... do that ...
fi
```

> builtins - 如果命令名称不包含斜杠，shell 会尝试定位它。如果存在同名的 shell 函数，则调用该函数，如上文 FUNCTIONS 中所述。如果名称与函数不匹配，shell 会在 shell 内置函数列表中搜索它。如果找到匹配项，则调用该内置函数。
> 如果名称既不是 shell 函数也不是内置函数，并且不包含斜杠，bash 会在 PATH 的每个元素中搜索包含该名称的可执行文件的目录。 Bash 使用哈希表来记住可执行文件的完整路径名（请参阅下面的 SHELL BUILTIN COMMANDS 下的哈希）。仅当在哈希表中找不到该命令时，才会对 PATH 中的目录进行完整搜索。如果搜索不成功，shell 将搜索一个已定义的名为 command_not_found_handle 的 shell 函数。如果该函数存在，则使用原始命令和原始命令的参数作为其参数调用它，并且该函数的退出状态变为 shell 的退出状态。如果未定义该函数，shell 将打印一条错误消息并返回退出状态 127。

#### [ ] 与 [[ ]]的区别

- [[ ]] 结构是 [ ] 的更通用的Bash版本。是扩展了的test命令

- [[ 和 ]] 之间没有文件名扩展或分词，但有参数扩展和命令替换。
  
  ```bash
  file=/etc/passwd
  
  if [[ -e $file ]]
  then
      echo "Password file exists."
  fi
  ```

- 使用[[ ... ]] 可以避免许多脚本中的逻辑错误，如，&&, ||, < 和 >操作符在[[ ]] 测试中奏效，而在[ ]结构中报错。

- 八进制/十六进制常数的算术评估在 [[ ... ]] 构造中自动进行。
  
  ```bash
  # [[ Octal and hexadecimal evaluation ]]
  ```

- 在 if 之后，无论是 test 命令还是测试括号（ [ ] 或 [[ ]] ）都不是绝对必要的。
  
  ```bash
  dir=/home/bozo
  if cd "$dir" 2>/dev/null; then
  # 2>/dev/null 隐藏了错误信息
     echo "Now in $dir."
  else
     echo "Can't change to $dir."
  fi
  # if COMMAND 返回COMMAND的退出状态
  ```

#### test - 检查文件类型和比较值

`-n string`     string的长度非零  == `string`

`-z string`     string长度为零

`string1 = string2`    the strings are equal    == `string1 -eq string2`

`string1 != string2`    the strings are not equal

`-ge`, `-gt`, `-le`, `-lt`, `-ne`, 

#### sed - Stream EDitor

`sed` 充当没有交互界面的文本编辑器。有助于选择文本、替换文本、修改原始文本、向文本添加行或从文本中删除行等操作。

```bash
sed OPTIONS [Script] [Inputfilename]
```

- `options` 控制Linux命令的输出

- `script` 包含一系列要运行的 Linux 命令

- `filename` 表示你正在使用sed命令的文件

##### Examples

- Replacing or substituting string
  
  ```bash
  $sed 's/unix/linux/' geekfile.txt   # 使用 linux 替换 unix
  
  # s 代表替代操作，’/‘是分割符，'unix'是search pattern，'linux'是替换串
  # 默认只替换第一个search pattern
  ```

- Replacing the nth occurrence of a pattern in a line（替换一行中第n次出现的pattern）。使用/1, /2等flags替换行中第一次，第二次出现的模式串。
  
  ```bash
  $sed 's/unix/linux/2' geekfile.txt
  ```

- Replacing all the occurrence of the pattern in a line （/g全局替换，指定 sed 命令替换该文本所有出现的字符串）
  
  ```bash
  $sed 's/unix/linux/g' geekfile.txt
  $sed 's/unix/linux/3g' geekfile.txt    # 替换文本从字符串第n次出现后的所有出现的
  ```

- Replacing string on a specific line number （可以限制 sed 命令以替换特定行号上的字符串。）
  
  ```bash
  $sed '3 s/unix/linux/' geekfile.txt    # 替换第三行上的串
  ```

#### 特殊字符

- `**`
  
  - 指数操作符
    
    ```bash
    let "z=5**3"    # 5 * 5 * 5
    echo "z = $z"   # z = 125
    ```
  
  - 扩展文件匹配通配符，新的`**`通配符递归匹配文件名和目录
    
    ```bash
    #!/bin/bash4
    shopt -s globstar  # Must enable globstar, otherwise ** doesn't work
    
    echo "Using *"; echo
    for filename in *
    do 
        echo "$filename"
    done    # Lists only files in current directory
    echo; echo "----------------"; echo
    
    echo "Using **"
    for filename in **
    do
        echo "$filename"
    done    # Lists complete file tree, recursively
    ```

- `?`
  
  - 在双括号结构中，`?`充当C风格的三元操作符，测试操作符
    
    `(( condition?result-if-true:result-if-false ))`
  
  - 在参数替代表达式中，`?`测试一个变量是否已经被设置
    
    `${variablename?}`构造也可以检查脚本中设置的变量，`${variablename?"ERROR MESSAGE"}`可以制定错误消息
  
  - wild card，在匹配文件名扩展是充当单个字符的通配符，在扩展正则表达式中表示一个字符。

- `$`
  
  - 变量替代，$variable表示variable代表的值
  
  - 行尾，在正则表达式中，$表示一行文本的末尾

- `${}`
  
  - 参数替换，\${parameter}和\$parameter一样，是变量parameter的值。但某些情况下，只有\${parameter}奏效
  
  - 可用于将变量与字符串连接起来。
    
    ```bash
    myid="${yourid} is not right"
    echo ${myid}
    ```

- `$'...'`
  
  - 带引号的字符串扩展结构，此构造将单个或多个转义的八进制或十六进制值扩展为 ASCII 或 Unicode 字符。如`echo -e $unicode_var`
    
    ```bash
    $ echo -e '\u2630'
    ☰
    # == echo -e '\xE2\x98\xB0' 可被早期Bash版本识别
    ```

- `$?`
  
  - 退出状态变量。持有命令，函数，脚本的退出状态

- `$$`

  - 进程ID变量。$$ 变量持有其出现的脚本的进程 ID。

- `()`
  
  - command group，命令组。括号内的命令列表开始一个子shell。括号内的变量，在子shell中，对脚本的其余部分不可见。父进程脚本无法读取子进程子shell中创建的变量。
  
  - array initialization，数组初始化。`Array=(element1 element2 element3)`

- `{xxx, yyy, zzz,...}`
  
  - Brace expansion，大括号扩展。大括号内不允许有空格，除非空格被引用或转义。shell进行大括号扩展。命令如cat,cp本身作用于扩展的结果。
    
    ```bash
    echo \"{These,words,are,quoted}\"
    # "These" "words" "are" "quoted"
    cat {file1,file2,file3} > combined_file
    # 连接file1 file2, and file3 到 combined_file22.
    cp file22.{txt,backup}
    # Copies "file22.txt" to "file22.backup"
    ```

- `{a..z}`
  
  - 扩展的大括号扩展
    
    ```bash
    echo {a..z}    # a b c ... z
    echo {0..2}
    
    base64_charset=({A..Z} {a..z} {0..9} + / = )
    ```

- `{}`
  
  - Block of code, 代码块。也被称作内联组。这种结构创建一个匿名函数。不像标准函数，代码块中的变量对脚本的其余部分仍可见。
    
    ```bash
    a=123
    { a=321; }
    echo "a = $a"    # a = 321
    ```
    
    与（括号）中的命令组不同，如上所述，由 {braces} 括起来的代码块通常不会启动子shell

- `[]`
  
  - test，测试[ ]中的表达式，分析见上文。
  
  - 数组元素，括号设置了数组中每个元素的编号
  
  - range of characters，作为正则表达式的一部分，方括号描述了要匹配的字符范围。

- `$[...]`
  
  - 整数扩展，计算 $[ ] 之间的整数表达式。
    
    ```bash
    a=3
    b=7
    echo $[$a+$b]    # 10
    echo $[$a*$b]    # 21
    ```
    
    > 请注意，此用法已被弃用，并已被 (( ... )) 构造取代。

- `(())`
  
  - 整数扩展，计算(( ))中的整数表达式
  
  - 允许在Bash中进行C风格的变量操纵
    
    ```bash
    (( a = 23 ))    # C风格设置变量,“等号两侧有空格”
    (( a++ ))    # Post-increment 'a' C-style
    # --------------------------------------
    # 注意，就像在C中，pre-和post-decrement操作符有不同的效果
    n=1; let --n && echo "True" || echo "False"    # False
    n=1; let n-- && echo "True" || echo "False"    # True 
    ```

- `>  &>  >&  >>  <  <>`
  
  - 重定向，**scriptname >filename** 重定向 **scriptname**脚本的输出到文件**filename**。如果**filename**文件已存在则覆盖之。
  
  - **command &>filename**重定向指令的stdout和stderr到filename
    
    ```bash
    $ type rmdir &>/dev/null
    $ echo $?
    0
    ```
  
  - **command >&2**重定向命令的stdout到stderr
  
  - **scriptname >>filename**将 scriptname 的输出附加到文件 filename。如果文件名不存在，则创建它。
  
  - **[i]<>filename**打开filename进行读写，并为其分配文件描述符i。如果文件名不存在，则创建它。

- `<<`
  
  - 被称为`here-document`结构，让程序知道文本末尾是什么，每当看到该分隔符时，程序都会读取您提供给程序的所有内容作为输入并对其执行任务。
    
    ```bash
    $ wc << EOF
    > one two three
    > four five
    > EOF
    2 5 24    (2行5个单词24个字符)
    ```

- `<<<`
  
  - `here-string`，无需输入文本，而是将预先制作的文本字符串提供给程序。如，`bc <<< 5*4`可以获取特定情况的输出，而无须交互式运行bc。可认为其等价于`echo '5*4' | bc`。

- `< <`
  
  - `< <`是语法错误，没有该操作符。
  
  - `< <()`是结合重定向（`<`）的进程替换(`<()`)。
    
    ```bash
    $ wc -l < <(grep ntfs /etc/fstab)
    4
    $ wc -l <(grep ntfs /etc/fstab)
    4 /dev/fd/63
    # command1 < <( command2 )
    ```

- `<`, `>`
  
  - ASCII 比较，在`[]`中需要用 \ 转义，而在`[[]]`中不需要。

- `\<`, `\>`
  
  - 转义尖括号--标记单词界限。
  
  - 尖括号必须被转义，否则它们只有字面字符含义。
  
  - "\\<the\>"匹配单词"the"，但不匹配"them"，"there"等。

- `|`
  
  - 管道，传递前一条命令的输出（stdout）到下一条命令或shell的输入（stdin）。经典进程间通信。
  
  - 命令的输出或命令也可能被管道输入到一个脚本，`ls -l | ./uppercase.sh`
  
  - 如果管道中的命令之一中止，则会过早终止管道的执行。这种情况称为损坏的管道，会发送一个 SIGPIPE 信号。

- `>|`
  
  - 强制重定向，即使设置了noclobber选项。这将强制覆盖现有文件。

- `||`, `&&`
  
  - 逻辑操作符。

- `&`
  
  - 在后台运行任务。在一条命令后加&，将使其在后台运行。
    
    ```bash
    $ sleep 10 &
    ```
  
  - 在脚本中，命令甚至循环都可能在后台运行。
    
    ```bash
    #!/bin/bash
    # background-loop.sh
    for i in 1 2 3 4 5
    do 
        echo -n "$i "    # echo -n 不输出后面的换行符
    done &    # 在后台运行该循环，有时在第二次循环是执行
    for i in 11 12 13 14 15
    do 
        echo -n "$i"
    done
    # ------------------
    # 执行结果顺序具有不确定性
    # 脚本中在后台运行的命令看似会导致脚本挂起，等待击键。
    # 事实上，后台命令已经完成，并未挂起。在尾部加wait或重定向至文件或/dev/null
    # 可解决
    ```

- `-`
  
  - 选项前缀。命令或过滤器的选项标志；参数替换中默认参数`${parameter-default}`，`${parameter:-default}` （若未设置paramete，使用default）
    
    ```shell
    # 参数替换
    var1=1
    var2=2
    echo ${var1-$var2}    # 1
    echo ${var3-$var2}    # 2
    
    echo ${username-`whoami`}
    # 如果变量$username unset, 输出`whoami`的结果
    ```
    
    ```markdown
    COMMAND -[Option1][Option2][...]
    sort -dfu $filename
    
    if [ "$c" -eq 24 -a "$d" -eq 47 ]
    then
        echo "$c equals 24 and $d equals 47."
    fi
    ```

- `--`
  
  - double-dash，命令长参数的前缀
  
  - 使用带有`--`选项的set命令将变量的内容显式分配给位置参数。如果`--`后没有变量，则取消设置位置参数。
    
    ```shell
    #!/bin/bash
    variable="one two three four five"
    set -- $varibale
    # Sets positional parameters to the contents of "$variable".
    first_param=$1    # one
    second_param=$2    # two
    set --
    # Unsets positional parameters if no variable specified.
    first_param=$1    # null value
    second_param=$2    # null value
    ```
  
  - redirection from/to stdin or stdout
    
    ```shell
    (cd /source/directory && tar cf - .) | 
    (cd /dest/directory && tar xpvf  -)
    # 将整个文件树从一个目录移动到另一个目录
    # == cp -a /source/directory/* /dest/directory
    # == cp -a /source/directory/* /source/directory/.[^.]* /dest/directory
    # -------------------------------------------
    # 1) cd /source/directory
    #    源目录
    # 2）&&
    #    和，若 cd 成功，执行下一条指令
    # 3）tar cf - .
    #    c 意味着创建一个新的存档
    #    f file, 之后的 - 指定目标文件作为标准输出，在当前目录下执行(.)
    # 4) |
    #    piped to ...
    # 5) ( ... )
    #    a subshell
    # 6) cd /dest/directory
    #    切换到目标目录
    # 7) && 
    # 8) tar xpvf -
    #    'x' Unarchive, 'x' is a command, 'pvf' are options
    #    'p' Preserve ownership and file permissions
    #    'v' Send verbose messages to stdout
    #    'f' Read data from stdin
    ```
  
  - 先前工作目录。`cd -` 命令切换到上一个工作的目录，使用了`$OLDPWD`。
  
  - 减法操作符。

- `=`
  
  - 等于号， 赋值操作符（no space before and after）
  
  - string comparison operator。test 指令中的`=`, `-eq`

- `+`
  
  - 加号
  
  - 选项，使用`+`启用某个选项（减号禁用）
  
  - 在参数替换中，`+`作为变量扩展的替代值的前缀。
    
    ```shell
    # ${parameter+alt_value}, ${parameter:+alt_value}
    # 如果设置了parameter，使用alt_value，否则使用null字符串
    # 两种格式仅在parameter被声明且为空不同
    a=${param1:+xyz}
    echo "a = $a"    # a =
    
    param2=
    a=${param2:+xyz}    # a = 
    a=${param2+xyz}    # a = xyz
    ```

- `%`
  
  - 求余
  
  - 在不同上下文中，%是模式匹配操作符

- `~`
  
  - home 目录。对应于 $HOME 内部变量

- `~+`
  
  - 当前工作目录。对应于 $PWD 内部变量

- `~-`
  
  - 先前工作目录。对应于$OLDPWD内部变量

- `=~`
  
  - 在双括号内使用`=~`进行正则表达式匹配测试
    
    ```shell
    #!/bin/bash
    variable="This is a fine mess."
    # Regex matching with =~ operator within [[ double brackets ]]
    if [[ "$variable" =~ T.........fin*es* ]]
    # 注意，从bash 3.2版开始，去匹配的表达式无需在使用引号
    then
        echo "match found"
    fi
    ```
