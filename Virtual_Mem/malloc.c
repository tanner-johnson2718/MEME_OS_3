#include <stdlib.h>
#include <stdio.h>

int main()
{
    int x = 1024*1024;
    printf("b4 malloc\n");
    void* mem = malloc(x);
    printf("after malloc b4 free, ptr = %p\n", mem);
    free(mem);
    printf("after free\n");

    return 0;
}