# Hello World, A link to the past

In this installment we will examine the process of linking. In [hello world](../Hello_World/) we looked at the contents and format of an executable. Many of the contents of an executable are reserved for the process of linking. Thus linking is natural second topic. We will first look at static linking followed by dynamic linking. The end goal here is first to obviously understand this process, but secondly to answer our unanswered questions from the previous exercise. 

To highlight the process of linking we slightly complicated the classic hello world by placing the "hello world" string as global in a library accesed through an accesor function in the example library. The main entry point is contained in `exe.c` and this accesor is contained in `lib.c`.

## What exactly is GCC doing?

In order to fully understand linking, the reader should be aware that when we call `gcc` it produces an exe through several stages, each of which are seperate command line tools. These are Preprocessing (cpp) -> Compiler (cc) -> Assembling (as) -> Linking (ld). In this section we give a brief overview of exactly what happens when going from a `.c` to an ELF file that can be linked or executed.

### Preprocessing
Preprocessing outside the scope of this project, but this is the stage where preprocessor macros are evaluated.

Input)
```C
#define STRING "Hello"
char* string_ptr = STRING;

int get_str(int x) {
  return string_ptr;
}
```

Output `cpp lib.c ./lib.i`)
```C
# 1 "lib.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "lib.c"

char* string_ptr = "Hello";

char* get_str(int x) {
    return string_ptr;
}

```

The meaning of the directives at the top will be left for a later study and can be further researched [here](https://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html). The key take away here is that the preprocessor macro `STRING` has been evaluated based on its definition in the same file and the code file that actually gets compiled has a string literal in place of the macro.

### Compiling

Compilation is the process of turning C into assembly source code. Again a detailed investigation is outside of out current scope, but we as we will see several artifacts that are used in linking appear first in the assembly output. The input file is the `lib.i` intermediate file shown above and the output is the result of `cc -S lib.i`)

```assembly
	.file	"lib.c"             ; Create file type symbol table entry w/ name "lib.c"
	.text                       ; Make current active section .text
	.globl	string_ptr          ; Add "string_ptr" to symbol table as global
	.section	.rodata         ; Make and switch to .rodata section
.LC0:
	.string	"Hello"                   ; Place string literal into object at cur loc
	.section	.data.rel.local,"aw"  ; Define non reserved section with flags
	.align 8
	.type	string_ptr, @object       ; Sets symbol type to object (data)
	.size	string_ptr, 8             ; Sets symbol size
string_ptr:
	.quad	.LC0                      ; Allocate space object for pointer
	.text                             ; Switch to .text section
	.globl	get_str                   ; Add "get_str" to symbol table as global
	.type	get_str, @function        ; Define type to be function
get_str:                              ; Assebly of function entry point
.LFB0:
	.cfi_startproc
	endbr64                           ; Mark this locale as suitable for call
	pushq	%rbp                      ; Push Old stack frame base ptr 
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp                ; Set new stack frame base ptr
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)            ; 
	movq	string_ptr(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	get_str, .-get_str
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

```

After compilation proper, we a resemblance to an ELF file explored previously. Sections start to appear such as .text (compiled user code) and .rodata (string literals). It appears as though the `.LC0, .LFB0, and .LFE0` are compiler "local variables" that do not survive assembly. Also the .cfi directives are used in exception handling and outside our current scope. Regardless we can see two imporatant things here. First data funtions, and meta data are organized into sections via the `.section` directive. Second, we know have compiled aseembly instead of C code. Runnging through the above assembly we can see that we get a "recipe" for constructing our final ELF.

* [x86 ref](https://docs.oracle.com/cd/E26502_01/html/E28388/eoiyg.html)

### Assembling

Assembling creates the ELF output we are familiar with. The assembler is invoked via `as lib.s -o lib.o`. Execute `readelf -a lib.o --wide `)

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

## Static Linking

## Questions

* What role do header files play in linking?
* How are command line args passed?
* Return codes?
* .rela.eh_frame?
* x86 feature: IBT, SHSTK?
* OLD QUESTION, eh frames?
* Globals in two files?

## Resources

* [1] [CSAPP](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)(Chapter 7)