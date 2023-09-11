/*
 * =====================================================================================
 *
 *       Filename:  sort_odd_reverse_sort_even.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  09/27/2022 11:24:53 AM
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

int cmpfunc_asc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int cmpfunc_des(const void *a, const void *b)
{
    return -(*(int*)a - *(int*)b);
}

int main()
{
    int arr[10];
    int i = 0;
    while(i < 10)
    {
	scanf("%d", &arr[i]);
	i++;
    }
    int pivot = arr[0];
    i = 0;
    int j = 9;
    while(i < j)
    {
	while(i < j && !(arr[j]&1))
	{
	    j--;
	}

	if(i < j)
	{
	    arr[i++] = arr[j];
	}

	while(i < j && arr[i]&1)
	{
	    i++;
	}

	if(i < j)
	{
	    arr[j--] = arr[i];
	}
    }
    arr[i] = pivot;
    if(pivot&1)
    {
	i++;
    }
    qsort(arr, i, sizeof(int), cmpfunc_des);
    qsort(&arr[i], 10-i, sizeof(int), cmpfunc_asc);
    for(i = 0; i < 9; i++)
    {
	printf("%d ", arr[i]);
    }
    printf("%d", arr[9]);
    return 0;
}
