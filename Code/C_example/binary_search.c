:i
/*
 * =====================================================================================
 *
 *       Filename:  binary_search.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  09/15/2022 08:12:32 PM
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

int binary_search(int arr[], int tempvalue, int low, int high);

int cmpfunc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int *arr = malloc(sizeof(int)*n);

    int i;
    i = 0;
    while(i < n)
    {
	scanf("%d",&arr[i]);
	i++;
    }

    qsort(arr, n, sizeof(int),cmpfunc); 

    for(i = 0; i < m; i++)
    {
	int x;
	scanf("%d", &x);

	if(binary_search(arr, x, 0, n-1) == 1)
	    printf("YES\n");
	else
	    printf("NO\n");
    }
    return 0;
}

int binary_search(int arr[], int tempvalue, int low, int high)
{
    if(high >= low){
	int mid = (low+high)/2;
	if(arr[mid] == tempvalue)
	{
	    return 1;
	}
	if(arr[mid] > tempvalue)
	{
	    return binary_search(arr, tempvalue, low, mid-1);
	}
	if(arr[mid] < tempvalue)
	{
	   return binary_search(arr, tempvalue, mid+1, high);
	}
    
    }
    return 0;
}
