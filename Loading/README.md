# Hello World, What do you do?

In this installment we shall go back the typical hello world:

```C
#include <stdio.h>

int main(int argc, char** argv) {
    printf("Hello World\n");
    return 0;
}
```

The goal here is to understand all that extra junk that gets put into the elf, follow its execution with gdb, and look at it the process by which a program gets loaded into memory.


## Ret Codes and Command Line Args