#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 7
#define NUM 2

struct fraction get_sum(struct fraction a, struct fraction b);
struct fraction get_parameter(char *str);

struct fraction{
    int p;
    int q;
}Fraction;

int main()
{
    int num;
    scanf("%d", &num);
    getchar();
    struct fraction *total = malloc(sizeof(struct fraction)*num);
    int k = 0;
    char temp[MAX];
    while(num--){
	fgets(temp, MAX, stdin);
	total[k] = get_parameter(temp);
	k++;
    }
    struct fraction sum  = get_sum(total[0], total[1]);
    for(int i = 2; i < k; i++)
    {
	sum = get_sum(sum, total[i]);
    }
    if(sum.p % sum.q == 0)
    {
	printf("%d\n", sum.p/sum.q);
	return 0;
    }
    while(sum.p % 2 == 0 && sum.q % 2 == 0)
    {
	sum.p = sum.p / 2;
	sum.q = sum.q / 2;
    }
    while (sum.p % 3 == 0 && sum.q % 3 == 0)
    {
	sum.p = sum.p / 3;
	sum.q = sum.q / 3;
    }
    if (sum.p % 5 == 0 && sum.q % 5 == 0)
    {
	sum.p = sum.p / 5;
	sum.q = sum.q / 5;
    }
    printf("%d/%d\n", sum.p, sum.q);	
    return 0;
}

struct fraction get_sum(struct fraction a, struct fraction b)
{
    struct fraction c;
    c.p = a.p*b.q + a.q*b.p;
    c.q = a.q*b.q;
    return c;
}

struct fraction get_parameter(char *str)
{
    int i, j; 
    char p[NUM];
    char q[NUM];
    struct fraction temp;
    i = j = 0;
    while(str[i]!='/')
    {
	p[j] = str[i];
	i++;
	j++;
    }
    if(j < 2){
	temp.p = p[0] - '0';
    }else{
	temp.p = atoi(p);
    }
    i++;
    j = 0;
    while(str[i]!='\0')
    {
	q[j] = str[i];
	i++;
	j++;
    }
    temp.q = atoi(q);
    return temp;
}
