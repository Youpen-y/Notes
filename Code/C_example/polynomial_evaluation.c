/*
 * =====================================================================================
 *
 *       Filename:  polynomial_evaluation.c
 *
 *    Description:  evaluation a1+a2x^2+a3x^3+...+anx^n
 *
 *        Version:  1.0
 *        Created:  09/11/2022 08:45:40 PM
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


float polynomial_evaluation (float arr[], int n, float x);
/* 
 * ===  FUNCTION ==================
 *         Name:  main
 *  Description:  functionality test for algorithm
 * ================================
 */
int main ( int argc, char *argv[] )
{
    int i, n;
    printf("输入系数个数: ");
    scanf("%d", &n);
    printf("依次输入系数: ");
    float * p = malloc(sizeof(float)*n);
    for(i = 0; i < n; i++)
    {
	scanf("%f", &p[i]);
    }
    printf("f(x) = ");
    for(i = 0; i < n-1; i++)
    {
	printf("%.2fx^(%d)+", p[i], i);
    }
    printf("%.2fx^(%d)\n", p[n-1], n-1);

    float x;
    char c;
    while(1){
	printf("输入x: ");
	scanf("%f", &x);
	getchar();
	printf("f(%.2f) = %f\n", x, polynomial_evaluation(p, n, x));
	printf("if go on (y/n)? ");
	if ((c = getchar()) == 'n')
	    break;
    }
    return 0;
}

/* 
 * ===  FUNCTION =================
 *         Name:  polynomial_evaluation
 *  Description:  algorithm for polynomial evalution
 * ===============================
 */
float polynomial_evaluation (float arr[], int n, float x)
{
    int i;
    float result = arr[n-1];

    for (i = n-2; i >= 0; i--)
    {
	result = result*x + arr[i];
    }
    return result;
}
