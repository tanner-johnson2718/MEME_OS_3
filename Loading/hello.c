#include <stdio.h>

void* stack_base;

void* rela(void* in)
{
    return (void*)(in - stack_base);
}

int main(int argc, char** argv, char** envp) {

    asm(
        "mov %%rbp, %0;"
        :"=r"(stack_base)
        :
        :
    );

    printf("Main Stack Base = %p\n", stack_base);
    printf("argc = %d\n", argc);
    printf("argv = %p\n",  rela((void*)argv));
    printf("envp = %p\n\n",  rela((void*)envp));

    int i = 0;
    while(argv[i] != NULL)
    {
        printf("argv[%d] = %p    *argv[%d] = %s\n", i,  rela((void*)argv[i]), i, argv[i]);
        ++i;
    }

    printf("\n");
    i = 0;
    while(envp[i] != NULL)
    {
        printf("envp[%d] = %p    *envp[%d] = %s\n", i,  rela((void*)envp[i]), i, envp[i]);
        ++i;
    }
}