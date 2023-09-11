/*
 * =====================================================================================
 *
 *       Filename:  insertion_sort.c
 *
 *    Description:  insertion sort algorithm
 *
 *        Version:  1.0
 *        Created:  09/14/2022 10:43:48 AM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

void insertion_sort(int array[], int n);
void printarray(int array[], int n);

int main()
{
    int arr[] = {10, 11, 5, 7, 43, 4, 1, 0, 56, -1};
    int num = sizeof(arr) / sizeof(int);
    insertion_sort(arr, num);
    return 0;
}

void insertion_sort(int array[], int n)
{
    int i, j;	/* counter */
    int temp;	/*  temp storage variable */

    for(i = 1; i < n; i++)
    {
	temp = array[i];	/* insert temp value to previous array[0..i-1] */
	j = i - 1;
	while(j >= 0 && array[j] > temp)
	{
	    array[j+1] = array[j];
	    j = j - 1;
	}
	array[j+1] = temp;
	printarray(array, n);
    }
}

void printarray(int array[], int n)
{
    int i;

    printf("array = ");
    for(i = 0; i < n-1; i++)
    {
	printf("%d ", array[i]);
    }
    printf("%d\n",array[i]);
}
