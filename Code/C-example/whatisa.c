#include <stdio.h>

int a = 1;

int func()
{
    int a = 2;
    if (a == 1){
	a = 10;
    }
    return a;
}

int main()
{
    printf("global a = %d\n", a);
    printf("a = %d\n", func());
    printf("global a = %d\n", a);
    return 0;
}



