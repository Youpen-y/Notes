/*
 * =====================================================================================
 *
 *       Filename:  check_endian.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  10/04/2022 08:54:00 AM
 *       Revision:  none
 *       Compiler:  gcc/clang
 *
 *         Author:  YangYuPeng, Yongy2022@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int checkCPU()
{
    union{
	int a;
	char b;
    }c;
    c.a = 1;
    return (c.b == 1);
}

int main()
{
    if(checkCPU())
    {
	printf("Little endian\n");
    }
    else
    {
	printf("Big endian\n");
    }
    int foo = 0x12345678;
    unsigned char* p = (unsigned char*)&foo;
    printf("%x ", p[0]);
    printf("%x ", p[1]);
    printf("%x ", p[2]);
    printf("%x ", p[3]);
    return 0;
}
