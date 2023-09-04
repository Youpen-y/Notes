### Shell code snippets

### Reference: [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/index.html)

#### 1. 测试是否采用正确数量的参数调用脚本

```bash
E_WRONG_ARGS=85
script_parameters="-a -h -m -z"
#                  -a = all, -h = help

if [ $# -ne $Number_of_expected_args]
then
    echo "Usage: `basename $0` $script_parameters"
    exit $E_WRONG_ARGS
fi
```

\`basename \$0\`：是脚本文件名，$0是脚本路径名，`basename filepath` 输出执行指令后的结果。

#### 2. Simple array usage

```bash
# 数组元素可以通过variable[xx]初始化。
# 或者，脚本可以通过显式的 declare -a variable 语句引入整个数组。
# 要解引用数组元素，请使用大括号表示法，即 ${element[xx]}。

# Array members need not be consecutive or contiguous
# 一些数组成员可以保持未初始化，数组中的间隙允许
# 稀疏数组在电子表格处理软件中很有用
```

```bash
#!/usr/bin/env bash
area[11]=23
area[13]=37
area[51]=UFOs

echo ${area[11]}    # {} 需要大括号
echo ${area[43]}    # 未初始化数组变量打印空白（空变量）

area[5]=`expr ${area[11]} + ${area[13]}`
echo ${area[5]}
# --------------------------------------------
# 赋值数组变量的另一种方式 array_name=( XXX YYY ZZZ ... )
area2=( zero one two three four )
echo ${area2[0]}    # zero
# --------------------------------------------
# 第三种方式 array_name=( [xx]=XX [yy]=YYY ... )
area3=([17]=seventeen [24]=twenty-four)

#
# --------------------------------------------
#
# Bash允许对变量进行数组操作，即使变量没有显式声明为数组
string=abcABC123

echo ${string[@]}    # abcABC123
echo ${string[*]}    # abcABC123
echo ${string[0]}    # abcABC123
echo ${string[1]}    # No output!
echo ${#string[@]}    # One element in the array
                      # The string itself
```

#### 备份昨天修改的文件

```shell
#!/bin/bash

# Backs up all files in current directory modified within last 24 hours
# in a "tarball" (tarred and gzipped file)
BACKUPFILE=backup-$(date +%m-%d-%Y)
#                Embeds date in backup filename
archive=${1:-$BACKUPFILE}
# If no backup-archive filename specified on command-line
# It will default to "backup-MM-DD-YYYY.tar.gz"

find . -mtime -1 -type f -print0 | xargs -0 tar rvf "$archive.tar"
gzip $archive.tar
echo "Directory $PWD backed up in archive file \"$archive.tar.gz\"."
```
