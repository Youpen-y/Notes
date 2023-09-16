#include<stdio.h>
#include<stdlib.h>

#define N 100001
#define MAX(a, b) ((a)>(b)?(a):(b))
int main()
{
    int day_profit[N];
    int sum_profit[N];
    int num;
    scanf("%d", &num);
    int i;
    for(i = 0; i < num; i++)
    {
	scanf("%d", &day_profit[i]);
    }
    sum_profit[0] = day_profit[0];
    for(i = 1; i < num; i++)
    {
	sum_profit[i] = MAX(day_profit[i], sum_profit[i-1] + day_profit[i]);
    }
    int max_sum_profit = sum_profit[0];
    for(i = 1; i < num; i++)
    {
	if(sum_profit[i] > max_sum_profit)
	    max_sum_profit = sum_profit[i];
    }
    printf("%d\n", max_sum_profit);
    return 0;
}



