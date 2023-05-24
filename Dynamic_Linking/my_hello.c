#include <my_puts.h>

void _start() {
    my_puts("Bra\n", 4);

    asm(
        "mov $60, %rax\n"
        "syscall"
    );
}