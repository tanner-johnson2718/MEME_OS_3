static void my_write(int fd, char* buf, long len)
{
    asm("mov $1, %rax\n"
        "syscall\n");
}

void my_puts(char* str, long len)
{
    my_write(1, str, len);
}

void _my_read(int fd, char* buf, int c)
{
    asm(
        "mov $0, %rax\n"
        "syscall\n"
    );
}

void wait()
{
    _my_read(0, 0, 1);
}

// Call assembly syscall to exit the process
void my_exit()
{
    asm(
        "mov $60, %rax\n"
        "syscall\n"
    );
}

void _start()
{
    my_puts("ENTER\n", 6);
    wait();
    my_puts("LEAVE\n", 6);
    my_exit();
}