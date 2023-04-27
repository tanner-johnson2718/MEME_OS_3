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

* `readelf -a hello` dumps entire output file (ELF format)
* ELF header contains meta data on exe. More importantly it points to program header and section header, the two views of an ELF.:

```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1060
  Start of program headers:          64 (bytes into file)
  Start of section headers:          14712 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
```

* C structure of an elf file defined at `/usr/include/elf.h`
* Program Header:
    * Table of segments
        * Which themselves are composed of sections.
    * Appears to describe program layout in memory.
    
## Resources
* https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
* https://github.com/compilepeace/BINARY_DISSECTION_COURSE/blob/master/ELF/ELF.md

# Questions
* **Q** When I run `./hello` how does it know read ELF header and process it accordingly.
    * **A** ELF file formats defined at `/usr/include/elf.h`
* **Q** What exactly happens when I excute this bash command?
    * **A** 
* **Q** In program header why is virt addr and phys addr the same?
* **Q** In program header why is stack mem size 0?
* **Q** How does it determine entry point?
    * **A** Matches with offset of .text. This must be where actual machine code of program is stored within ELF?
* **Q** Intereter `/lib64/ld-linux-x86-64.so.2`??