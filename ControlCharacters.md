#### Control Characters

改变文本展示或终端的行为。控制字符是 CONTROL + key 组合。控制字符也可以被写成跟在转义符后的八进制或十六进制表示法。

控制字符在脚本中通常没有用处。

- Ctrl-A
  
  将光标移到文本行的开始处（命令行）

- Ctrl-B
  
  退格Backspace（非破坏性）

- Ctrl-C
  
  Break 终止一个前台任务

- Ctrl-D
  
  从shell登出（与exit相似）
  
  **EOF** （end of file） 从标准输入中断输出
  
  在控制台或 xterm 窗口中键入文本时，Ctl-D 会擦除光标下的字符。当不存在字符时，Ctl-D 会按预期退出会话。在 xterm 窗口中，这具有关闭窗口的效果。

- Ctrl-E
  
  将光标移至文本行尾（命令行上）

- Ctrl-G
  
  在一些老式的电传终端上，将ring a bell。在xterm，将发出哔哔声。

- Ctrl-H
  
  在退格时擦除光标后退的字符。

- Ctrl-J
  
  Newline，在脚本中，可能以八进制'\012'或十六进制'\x0a'表示。

- Ctrl-L
  
  终端清屏

- Ctrl-M
  
  Carriage return

- Ctrl-R
  
  回溯搜索历史缓冲区中的文本

- Ctrl-U
  
  清除一行输入，从光标至行首。在某些设置下，Ctrl-U清除整行输入。

- Ctrl-V
  
  在输入文本时，Ctrl-V允许插入控制字符。如，下面等价
  
  ```shell
  echo -e '\x0a'
  echo <Ctrl-V><Ctrl-J>
  ```

- Ctrl-W
  
  在控制台或 xterm 窗口中键入文本时，Ctl-W 会从光标下的字符向后擦除到第一个空白符。在某些设置中，Ctl-W 向后擦除到第一个非字母数字字符。

- Ctrl-X
  
  在某些字处理程序中，剪切高亮的文本并拷贝到粘贴板（clipboard）

- Ctrl-Y
  
  粘贴回之前（使用Ctrl-U或Ctrl-W）删除的文本

- Ctrl-Z
  
  暂停前台工作。
  
  某些文字处理应用程序中的替换操作。
  
  MSDOS文件系统中的EOF字符。

- $IFS
  
  分隔特定命令输入字段（fields of input）的特殊变量。它默认为空格。
  
  > 要在字符串或变量中保留空格，请使用引号。

#### POSIX Character Classes [:class:]

指定要匹配的字符范围的另一种方法

- [:alnum:]
  
  匹配字母或数字字符。相当于A-Za-z0-9

- [:alpha:]
  
  匹配字母。A-Za-z

- [:blank:]
  
  匹配space或tab

- [:cntrl:]
  
  匹配控制字符

- [:digit:]
  
  匹配数字。0-9

- [:graph:]
  
  (graphic printable characters)，匹配ASCII中33-126范围内的字符。等价于不含space 字符的[:print:]

- [:lower:]
  
  匹配小写字母字符。a-z

- [:print:]
  
  (printable characters)，匹配ASCII中32-126范围内的字符。

- [:space:]
  
  匹配空格字符（space and horizontal tab）

- [:upper:]
  
  匹配大写的字母字符，A-Z

- [:xdigit:]
  
  匹配十六进制数字，0-9A-Fa-f

> POSIX character classes通常需要引号或双括号

#### Parameter Substitution （参数替换）

操纵和/或扩展变量

- `${parameter}`
  
  == $parameter 即变量parameter的值。\${parameter}无歧义。
  
  ```shell
  your_id=${USER}-on-${HOSTNAME}
  echo "$your_id"
  #
  echo "Old \$PATH = $PATH"
  PATH=${PATH}:/opt/bin
  echo "New \$PATH = $PATH"
  ```

- `${parameter-default}, ${parameter:-default}`
  
  如果parameter未设置，使用default。区别：当parameter被设为空，前者使用parameter，后者采用default。

> 默认参数构造可用于在脚本中提供缺失的命令行参数
> 
> ```bash
> DEFAULT_FILENAME=generic.data
> filename=${1:-$DEFAULT_FILENAME}
> # 如果没有另外的指定，以下命令块运行在文件generic.data
> # Begin-Command-Block
> # ...
> # ...
> # End-Command-Block
> # -----------------------------------------------
> DISKS=${1:-E_NOPARAM}    # Must specify how many disks
> # 如果提供了$1的话，设定$DISKS为$1命令行参数。
> # 如果没有提供$1的话，设定为$E_NOPARAM
> ```

- `${parameter+alt_value}, ${parameter:+alt_value}`
  
  如果参数未设置，使用alt_value，否则使用null string。

- `${parameter?err_msg}, ${parameter:?err_msg}`
  
  如果参数设置了，使用它。否则打印err_msg并且终止脚本，退出状态为1。
  
  仅当parameter设置为空时，有区别，区别同上。
  
  ```shell
  #!/bin/bash
  # usage-message.sh
  : ${1?"Usage: $0 ARGUMENT"}
  # Script exits here if command-line parameter absent
  # with following error message.
  #    usage-message.sh: 1: Usage: usage-message.sh ARGUMENT
  # ... 
  # 如果命令行缺失，$? 为1
  # 如果命令行存在，$? 为0
  ```


