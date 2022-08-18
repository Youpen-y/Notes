### Test

#### Test Constructs

- `if/then`

- `[` （出于效率原因，Bash内置）, `test`的同义词。  

- `[[` 关键字， ``[[ ... ]]`扩展测试命令

- `((...))`和`let ...`结构根据是否它们评估的表达式扩展为一个非0值返回一个退出状态。这些算术扩展结构可以被用来执行算术比较。
  
  > The "let" construct returns the same exit status as the double-parentheses arithmetic expansion.
  > 
  > ```shell
  > (( 0 && 1 ))     # 逻辑和
  > echo $?     # 1
  > let "num = (( 0 && 1 ))"
  > echo $num   # 0
  > let "num = (( 0 && 1 ))"
  > echo $?     # 1
  > ```

`if` 可以测试任何指令，而不仅仅是括号内的条件。

```shell
if grep -q Bash file
    then echo "File contains at least one occurrence of Bash"
fi
```

`[[]]`结构是`[]`更通用的Bash版本，是扩展的test命令，从 ksh88 采用。

```shell
file = /etc/passwd
if [[ -e $file ]]
then
    echo "Password file exists."
fi
```

使用 `[[ ... ]] `测试结构，而不是 `[ ... ]` 可以防止脚本中的许多逻辑错误。例如，`&&`、`||`、`<`和`>`运算符在 `[[ ]]` 测试中工作，尽管在 `[]`构造中给出错误。


