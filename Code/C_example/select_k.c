/*
 * =====================================================================================
 *
 *       Filename:  select_k.c
 *
 *    Description:  select the k_th element from array(ascending order)
 *
 *        Version:  1.0
 *        Created:  09/13/2022 03:24:27 PM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

// function declaration
int select(int arr[], int n, int k);

int main()
{
    int arr[] = {10, 7, 0, 4, 3, 2, 1};
    printf("%d\n", select(arr, sizeof(arr)/sizeof(int), 1));
    return 0;

}

int select(int arr[], int n, int k)
{
    int pivot = arr[0];
    int splus[n];
    int sminus[n];
    int j, m;
    j = m = 0;
    for(int i = 1; i < n; i++)
    {
	if(arr[i] < pivot)
	{
	    sminus[j] = arr[i];
	    j++;
	}
	else
	{
	    splus[m] = arr[i];
	    m++;
	}
    }
    if(j == k-1)
	return arr[0];
    else if(j > k-1)
	return select(sminus, j, k);
    else
	return select(splus, m, k-j-1);
}
