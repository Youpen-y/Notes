### Shell code snippets
### Reference: [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/index.html)


#### 1、测试是否采用正确数量的参数调用脚本

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

\`basename \$0\`：是脚本文件名
