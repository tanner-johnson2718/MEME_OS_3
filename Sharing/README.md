# Sharing, A Link to the Past

In this installment we will examine the process of linking. In [hello world](../Hello_World/) we looked at the contents and format of an executable. Many of the contents of an executable are reserved for the process of linking. Thus linking is natural second topic. We will first look at static linking followed by dynamic linking. The end goal here is first to obviously understand this process, but secondly to answer our unanswered questions from the previous exercise.

## Static Linking

In static linking ALL compiled code is copied and contained in the final executable. To highlight this process we have two C files, `exe.c` and `lib.c`. `exe.c` will contain our main function and it will call a single function from `lib.c`. The first step is to compile our "library", `gcc -c lib.c`, which produces `lib.o`.

* Execute `readelf -a lib.o --wide `

```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          608 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         12
  Section header string table index: 11

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        0000000000000000 000040 00001b 00  AX  0   0  1
  [ 2] .data             PROGBITS        0000000000000000 00005b 000000 00  WA  0   0  1
  [ 3] .bss              NOBITS          0000000000000000 00005b 000000 00  WA  0   0  1
  [ 4] .comment          PROGBITS        0000000000000000 00005b 00002c 01  MS  0   0  1
  [ 5] .note.GNU-stack   PROGBITS        0000000000000000 000087 000000 00      0   0  1
  [ 6] .note.gnu.property NOTE            0000000000000000 000088 000020 00   A  0   0  8
  [ 7] .eh_frame         PROGBITS        0000000000000000 0000a8 000038 00   A  0   0  8
  [ 8] .rela.eh_frame    RELA            0000000000000000 0001e0 000018 18   I  9   7  8
  [ 9] .symtab           SYMTAB          0000000000000000 0000e0 0000f0 18     10   9  8
  [10] .strtab           STRTAB          0000000000000000 0001d0 00000e 00      0   0  1
  [11] .shstrtab         STRTAB          0000000000000000 0001f8 000067 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

There are no section groups in this file.

There are no program headers in this file.

There is no dynamic section in this file.

Relocation section '.rela.eh_frame' at offset 0x1e0 contains 1 entry:
    Offset             Info             Type               Symbol's Value  Symbol's Name + Addend
0000000000000020  0000000200000002 R_X86_64_PC32          0000000000000000 .text + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 10 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS lib.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     9: 0000000000000000    27 FUNC    GLOBAL DEFAULT    1 is_odd

No version information found in this file.

Displaying notes found in: .note.gnu.property
  Owner                Data size 	Description
  GNU                  0x00000010	NT_GNU_PROPERTY_TYPE_0	      Properties: x86 feature: IBT, SHSTK
```

* We an see from the above ELF dump that it is much simplier than the hello world ELF
* It pretty much only contains the code and meta data
* It contains no information on how to map any of the code or data sections into memory
    * No program headers
* Note the type is a relocatable file (hello world was a shared object file), which is essentially assembled code with no program headers.

Now we

## Questions

* What role do header files play in linking?
* How are command line args passed?
* Return codes?
* .rela.eh_frame?
* x86 feature: IBT, SHSTK?
* OLD QUESTION, eh frames?
* Globals in two files?

## Resources

* [1] [CSAPP](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)(Chapter 7)s