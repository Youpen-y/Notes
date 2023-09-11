/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  09/23/2022 10:30:51 AM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    int n;
    scanf("%d", &n);

    int *arr = malloc(sizeof(int)*n);

    int i = 0;
    while(i < n)
    {
	scanf("%d", &arr[i]);
	i++;
    }
    qsort(arr, n, sizeof(int), cmpfunc);

    i = 0;
    while(i < n)
    {
	if(arr[i]&1)
	{
	    printf("%d", arr[i]);
	    i++;
	    break;
	}
	i++;
    }

    while(i < n)
    {
	if(arr[i]&1)
	{
	    printf(",%d", arr[i]);
	}
	i++;
    }
    return 0;
}
