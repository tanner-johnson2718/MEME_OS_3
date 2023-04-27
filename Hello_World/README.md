# Hello World

* Code)

```C
#include <stdio.h>

int main(char** argv, int argc)
{
    printf("Hello World\n");
    return 0;
}
```

* Build) `gcc -o hello hello.c`.
* Execute) `./hello`

# Examining the output

* `readelf -a hello` dumps output (ELF format)
* ELF header contains meta data on exe. More importantly it points to program header and section header, the two views of an ELF
* C structure of an elf file defined at `/usr/include/elf.h`
* Program Header:
    * Table of segments
        * Which themselves are composed of sections.
    * Appears to describe program layout in memory.
    
## Resources
* https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
* https://github.com/compilepeace/BINARY_DISSECTION_COURSE/blob/master/ELF/ELF.md

# Questions
* When I run `./hello` how does it know read ELF header and process it accordingly.
    * **A** ELF file formats defined at `/usr/include/elf.h`
* What exactly happens when I excute this bash command?
    * **A** 
* In program header why is virt addr and phys addr the same?
* In program header why is stack mem size 0?
* **Q** How does it determine entry point?
    * **A** Matches with offset of .text. This must be where actual machine code of program is stored within ELF?
* Intereter `/lib64/ld-linux-x86-64.so.2`??