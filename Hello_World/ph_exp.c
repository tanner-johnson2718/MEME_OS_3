// Program to explore its own org in memory.

#include <stdio.h>
#include <stdlib.h>

int gbl_uninit;
int gbl_init = 0;
char* gbl_str = "GBL";

int func1(int x)
{
    return x+1;
}

int main(void) 
{
    unsigned char dummy = 0;
    char* local_str = "LCL";
    unsigned char* main_frame_stack_pos = &dummy;
    unsigned char* heap_start_pos = malloc(0x1000);

    printf("Main Frame Stack Pos = %p\n", main_frame_stack_pos);                // Top of address space (from main frame perspective)
    printf("printf rela Pos      = %p\n", (unsigned char*) printf);
    printf("malloc rela Pos      = %p\n", (unsigned char*) malloc);
    printf("Heap Start Pos       = %p\n", heap_start_pos);                      // ??
    printf("Un-Init Gobal Pos    = %p\n", (unsigned char*) &gbl_uninit);        // .bss
    printf("Init Gobal Pos       = %p\n", (unsigned char*) &gbl_init);          // .data
    printf("Local String Pos     = %p\n", (unsigned char*) local_str);          // .rodata +4
    printf("Global String Pos    = %p\n", (unsigned char*) gbl_str);            // .rodata
    printf("main Pos             = %p\n", (unsigned char*) main);               // .text + ?? + len(func1)
    printf("func1 Pos            = %p\n", (unsigned char*) func1);              // .text + ??
    return 0;
}