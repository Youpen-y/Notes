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

`$#`:    命令行参数总数

`$*`:    用来展示所有命令行参数

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
