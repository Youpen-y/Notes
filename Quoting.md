#### Quoting (引用)

引用意味着用引号括起一个字符串。具有保护字符串中的特殊字符不被shell或shell脚本重新解释或扩展的效果。（特殊字符指除了字面意思外有别的解释的字符）

引用变量时，通常建议用双引号将其名称括起来。

> Single Quotes 将字符括在单引号(')中会保留引号内每个字符的文字值。单引号之间不能出现单引号，即使前面有反斜杠。
> 
> Double Quotes 将字符括在双引号 (") 中会保留引号内所有字符的字面值，但 $, `, \ 以及启用历史扩展的 ! 除外。

```shell
hello="A B  C   D"
echo $hello    # A B C D
echo '$hello'    # $hello
echo "$hello"    # A B  C   D
```

引用可以抑制echo对换行符的“胃口”

```shell
$ echo $(ls -l)    # 输出不带换行符
$ echo "$(ls -l)"  # 输出包含换行符
```

此外，双引号可以防止词被划分，用双引号括起来的参数将其自身显示为一个单词，即使其中包含空格。

```shell
List="one two three"

for a in $List
do
    echo "$a"
done
# one
# two
# three
echo "-----"

for a in "$List"
do
    echo "$a"
done
# one two three
# 封装“！”从命时，双引号内会出错。这被解释为历史命令。
# 但是，在脚本中，不会发生此问题，因为 Bash 历史记录机制当时被禁用。
```

##### 转义（Escaping）

转义时引用单个字符的方式。字符前的转义符（\）告诉shell按字面值翻译字符。然而在与某些命令和实用程序结合使用时，如echo和sed，它可以切换该字符的特殊含义。

- `\n` 换行

- `\r` return，回退

- `\t` tab，制表符

- `\v` vertical tab

- `\b` backspace 空格

- `\a` alert （beep or flash）

- `\0xx` 译为八进制0nn，`$'...'`带引号的字符串扩展结构是一种使用转义的八进制或十六进制值将ASCII字符分配给变量的机制，如quote=$'\042'
