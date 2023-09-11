/*
 * =====================================================================================
 *
 *       Filename:  search.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  09/15/2022 07:29:08 PM
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

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int *arr = malloc(sizeof(int)*n);
    int *tempvalue = malloc(sizeof(int)*m);

    int i, j;
    i = 0;
    while(i < n)
    {
	scanf("%d",&arr[i]);
	i++;
    }
    i = 0;
    while(i < m)
    {
	scanf("%d", &tempvalue[i]);
	i++;
    }
    for(i = 0; i < m; i++)
    {
	for(j = 0; j < n; j++)
	{
	    if(tempvalue[i] == arr[j])
	    {
		printf("YES\n");
		break;
	    }
	}
	if(tempvalue[i] != arr[j])
	    printf("NO\n");
    }
    return 0;
}
