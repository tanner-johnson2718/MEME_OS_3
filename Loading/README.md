# Hello World, What do you do?

In this installment we shall go back the typical hello world:

```C
#include <stdio.h>

int main(int argc, char** argv) {
    printf("Hello World\n");
    return 0;
}
```

The goal here is to understand all that extra junk that gets put into the elf, follow its execution with gdb, and look at it how it gets dynamically linked with shared systems libraries.

## GDB

https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf