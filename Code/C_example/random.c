#include <stdio.h>
#include <stdlib.h>

int getRandomValue()
{
    srand(time(0));
    return rand();
}

int main()
{
    int i, a;

    for(i = 10; i > 0; i--)
    {
	a = getRandomValue();
	printf("%d: %d\n", (11-i), a);
    }
    return 0;
}

