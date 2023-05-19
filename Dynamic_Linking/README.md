# Hello World, Sharing is Caring

In the previous installment we looked at dynamic linking and how globals are linked statically. Here we shall look at dynamic linking. Some functions, such as the `printf` function are part of the standard library. Instead of copying the code for this functions that get used across many programs into each executable, these functions are laoded into memory by the OS and when we are program calling these funtions, references to them are linked and mapped at run time. In this installment we shall look at this process.

## Exercise, Make your own Print Shared Library

To start, let us make our own shared library. We will take our minimal hello world from the previous exercise, make it a shared library for putting a string on the terminal, and call it in a new hello world. Our library function `my_puts()` is implemented in `my_puts.c`)

```C
void my_write(int fd, char* buf, long len)
{
    asm("mov $1, %rax\n"
        "syscall\n");
}

void my_puts(char* str, long len)
{
    my_write(1, str, len);
}

```

It uses the [syscall](https://www.cs.uaf.edu/2017/fall/cs301/lecture/11_17_syscall.html) instruction to call the write system call on STDOUT. 

* https://opensource.com/article/22/5/dynamic-linking-modular-libraries-linux

## Progromattic INterface

## System Shared Libraries

* PLT and GOT?
* How do I see what shared libraries are currently resident in memory?
    * stdlib
    * libc
* crt1.0?
* When are these loaded on startup?
    * Or are they loaded on an as needed basis?

## Linker Script Clean up