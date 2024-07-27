#include <stdio.h>
#include <unistd.h>

int main() {
    long int page_size = getpagesize();
    printf("Page size: %ld bytes\n", page_size);
    return 0;
}

