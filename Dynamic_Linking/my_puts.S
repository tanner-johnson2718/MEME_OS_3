.section .text
.globl my_puts
my_puts:
    mov $4, %rax
    mov $1, %rbx
    lea msg(%rip), %rcx
    mov $5, %rdx
    int $0x80

.section .data
msg:
    .ascii "AAAA\n"
