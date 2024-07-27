#include <stdio.h>

int fibonacci(int n);

int main()
{
    int num;
    while(1)
    {
	printf("n = ");
	scanf("%d", &num);
	getchar();
	printf("fibonacci(%d) = %d\n", num, fibonacci(num));
	printf("if go on (y/n)? ");
	char c;
	if((c=getchar())=='n'||c=='N')
	    break;
    }
    return 0;
}

int fibonacci(int n)
{	
    if(n==0)
	return 0;
    else if(n==1)
	return 1;
    else
	return fibonacci(n-1)+fibonacci(n-2);
}

