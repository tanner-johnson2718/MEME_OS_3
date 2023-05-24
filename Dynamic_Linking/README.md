# Hello World, Sharing is Caring

In the previous installment we looked at static linking and how globals are linked statically. Here we shall look at dynamic linking. Some functions, such as the `printf` function are part of the standard library. Instead of copying the code for these functions that get used across many programs into each executable, these functions are loaded into memory by the OS and when a program calling these funtions references them, they are linked and mapped at run time. In this installment we shall look at this process.

## Exercise, Make your own Print Shared Library

To start, let us make our own shared library. We will take our minimal hello world (or something analogous) from the previous exercise, make it a shared library for putting a string on the terminal, and call it in a new hello world. Our library function `my_puts()` is implemented in `my_puts.c`)

```C
static void my_write(int fd, char* buf, long len)
{
    asm("mov $1, %rax\n"
        "syscall\n");
}

void my_puts(char* str, long len)
{
    my_write(1, str, len);
}

```

It uses the [syscall](https://www.cs.uaf.edu/2017/fall/cs301/lecture/11_17_syscall.html) instruction to call the write system call on STDOUT. The literal 1 is placed into the `rax` register to tell the syscall intruction to do a write. The register calling convention for `syscall` is exactly the same for C functions, thus our `my_write` wrapper can simply keep the same arguements as a write system call and pass them through in the same registers.

Now we compile this minimal hello world with the following two commands)

* `gcc -fPIC -c my_puts.c -fno-asynchronous-unwind-tables`
    * `-fPIC` gives us PC relative addressing and is thus posistion independand
    * `-fno-asynchronous-unwind-tables` gets rid of the eh sections in the finally elf as we will not use them
* `objcopy --remove-section=.note.gnu.property --remove-section=.note.GNU-stack --remove-section=.comment my_puts.o`.
    * This just strips some of the meta data so we have simplier output elf to analyze.

This produces a rather simple ELF and assembly code. It exports a single global function `my_puts` to be linked with our main hello world. It contains no relocation entries, an empty data section, and is just a symbol table and its assembly code.

Now we want to turn this object module into a shared library object. We do this with the following: `gcc -shared -nostdlib -o libM.so my_puts.o`. The ker here is the `-shared` flag indicating we want to create a shared object. Note that by linux convention, shared libraries shard with "lib" and are suffixed with ".so". This ouputs a shared object file `libM.so`. Dumping the ELF we see a few new sections we have not analyzed in depth yet. These are the `.dynsym`, `.dynstr`, and `.dynamic` sections.

* `.dynsym` + `.dynstr`) These serve the exact same purpose as the symbol table (and symbol string table) as explored in static linking. In this case, the dynamic symbol table of libM.so only contains an entry for `my_puts`, gives its offset into the ELF, and gives the usual meta data. Note here on key difference between the symbol table and its dynamic conuter part is the dynamic symbol table actually gets loaded into memory, where as the base symbol table is only stored in the file. This is obviously a key distinction as we need resolve these symbols at run time. Just as in static linking, objects that reference `my_puts` will get an undefined symbol to `my_puts` in their respective dynamic symbol table.

* `.dynamic` is an array of [structures](https://docs.oracle.com/cd/E23824_01/html/819-0690/chapter6-42444.html) that index the various sections and important details of the file used in dynamic linking such as `.dynsym`, `.dynstr`, the GNU hash table, etc.

Finally we can look at our actual hello world.

```C
#include <my_puts.h>

void _start() {
    my_puts("Bra\n", 4);

    asm(
        "mov $60, %rax\n"
        "syscall"
    );
}
```

We compile this with `gcc -nostdlib -fno-asynchronous-unwind-tables -I . -L./ my_hello.c -lM -o test`. There are some caviets associated with this which we list below.

* First the entry point is `_start` instead of `main`. This is because we are compiling without the standard library. The standard C library adds a wraper to our starting main code that handles input args, process exiting and clean up, etc. All processess by default start at the `_start` symbol (this is dictated by the linker).
* `-I .`. This flag just looks for include files in our current dir.
* `-L./`. Look for libraries in our current dir
* `-lM`. Look for library of name "libM.so". The lib and .so pre and postfix are implicitly added.
* One final gotcha is we mush add an envirmonet variable using the following command `export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH`. This tells the linker to also look at our current directory for libraries at runtime.

... Talk about new sections


### Key resource

* https://medium.com/@The_Mad_Zaafa/creating-and-using-dynamic-libraries-c-a9d344822ed0

## PLT and GOT

* If I reference my_puts twoce, is there only a single reloction entry?
    * SHould be right?
* How are .data and .text sections always at some distance from each other??
    * especially in shared libraries
* Lazy binding
* find addrs of .data and .text sections in example
* Add code to look at physical addresses?
* what happens when a second function calls into lib when the first ref. prog is still running 

## Progromattic Interface

## System Shared Libraries

* How do I see what shared libraries are currently resident in memory?
    * stdlib
    * libc
* crt1.0?
* When are these loaded on startup?
    * Or are they loaded on an as needed basis?
    * Once loaded, how does it know where it is??

* why is _start the entry, is it loader or linker?

## Linker Script Clean up