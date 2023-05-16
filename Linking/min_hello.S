.section .text
.globl _start
_start:
    mov $4, %rax
    mov $1, %rbx
    mov $msg, %rcx
    mov $6, %rdx
    int $0x80
    mov $1, %rax
    int $0x80

.section .data
msg:
    .ascii "Test\n"
