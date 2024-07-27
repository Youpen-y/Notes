/*
 * =====================================================================================
 *
 *       Filename:  roundoff.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  10/06/2022 09:14:23 AM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int main()
{
    double a;
    int i;

    a = 0.2;
    a += 0.1;
    a -= 0.3;

    printf("a = %f\n", a);
    
    for (i = 0; a < 1.0; i++)
    {
	printf("i = %d, a = %f\n", i, a);
	a += a;
    }

    printf("i = %d, a = %f\n", i, a);
    return 0;
}

