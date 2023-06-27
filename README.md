# MEME OS 3

In the first installment of MEME OS we built a virtual linux OS using build root, customized the kernel, and linked a GDB debugger to the kernel while executing in QEMU. In MEME OS 2 we created a bare bones OS and some bare metal drivers again targeting QEMU.

MEME OS 3 will take a bit of a detour. The eleavator pitch is **everything your 4000 level OS Comp Sci class should have been**. This project will be an exploration of a linux system running on actual hardware. We will treat our linux system as object of study. Starting from a hello world, we will look at things like:

* What does `#include <stdio.h>` do **exactly**?
    * Where are the definitions and declarations of libraries inlcude like this?
* Why is entry function `int main(..)`?
    * How are args passed?
    * Exit Codes?
    * Execution?
* What **exactly** happens when I call `printf("hello\n");`.

We will repeat this type of questioning and digging for increasingly complicated boiler plate C and linux code. The goal here being make precise and rigorious the exact system processes we take for granted while programming and use this type of "playing" or "exploring" as a mechanism for understanding how linux works, starting from hello world.

To keep projected well bounded we will implace the following contraints)

* Only look at what can be gathered from user space C programs, command line tools, and system interfaces. (Still include references to kernel code or headers but focus on what can be seen / interfaced with via a terminal or C program in user land).
* Use a singular program as a means to examine and exlempify a singular topic. Predefine what will be examined with each program. And push discussion of topics outside those predefined to a future program that will examine and highlight that topic.
* Make a road map of precisely what topics will be explored
* **Focus on the "hands on"**. Instead of pointing to a text book that explains how something works, write code and tinker with some example code to SHOW what the text book explains.

# Road Map

## Part 1, Hello World

We started with a simple hello world in C and this served as the boiler plate code that guided our exploration in part 1. Our very first question is: [what exactly is this output file](./Hello_World) we get when we compile a hello world. This lead to a "bullet-pointy" overview of the ELF format and its contents. Much of the contents of an ELF are used in the process of linking so that was a natural second topic. We started with [static linking](./Linking) where we described how symbols are used to "export" and "import" entities (functions, global variables, etc) shared between C files. We also looked at relocation which is how assembled C files are patched together so that references to symbols in other files are resolved. 

Static linking copies the code and data of assembled C files into every executable that uses said code and data. That's inefficient and [Dynamic Linking](./Dynamic_Linking) solves this issue. With dynamic linking we looked at how the PLT and GOT are used by the dynamic linker to resolve symbols at run time. Finally, we concluded our disection of the hello world by looking at how executables are [Loaded](./Loading) once its process is created. At the conclusion of Part 1, one should have a very good understanding about how one goes from a C hello world to an executable loaded in memory that uses system calls and references the C standard library to print "Hello" to the terminal.

* [X] [Hello World, What did you give me?](./Hello_World) (ELF File Format)
* [X] [Hello World, A link to the past](./Linking) (Static Linking and Archives)
* [X] [Hello World, Sharing is Caring](./Dynamic_Linking) (Dynamic Linking and Shared Libraries)
* [X] [Hello World, What do you do?](./Loading) (Loading a Process)

## Part 1.5

It was clear from part 1 that libc introduces all sorts of weirdness. To keep our exploration as pointed as possible and to eliminate any obfuscation of what our code is actually doing we are gonna write [our own libc](./MEME_Lib/). It gives us basic wrappers for commonly used system calls, some string manip, and anything else we add later.

## Part 2, Async

Part 2 is where we start to dig deeper into the kernel space. In part 1 we took for granted process creation and system calls without digging too deep into what happens before the dynamic linker or my entry point is given control. We also did not dig to deep into what happens when I raise a system call with the instruction `syscall` or analgously use the C standard library wrappers for system calls. Thus in this we part we dig into these concepts. Part one dealt with singular process, hello world. We coin this part Async b/c this where we start to look into the rabbit hole that is how several programs run concurrently.

We start with [processes](./Processes/) where we see what composes them, how they are created and how this construct is used by linux to do useful systems things. We saw that process require heavy use of [system calls](./System_Calls/) and we also relied heavily on system calls in part one, so much so that we created our own wrappers for common system calls in part 1.5. Thus system calls are a natural second topic in this part and an important topic, as system calls are the primary way user space can ask the kernel to do priviledged tasks on its behalf. Now process control flow, state, and concurrent execution rely on [signals](./Signals/) and so we next looked at how signals can be used to sychronize two concurrent processes. And finally, signals are a userspace constuct and [interrupts](./Interrupts/) are the underlying OS and hardware concept behind and thus we concluded this part with an exploration of interrupts.

* [X] [Processes and Threads](./Processes)
* [ ] [System Calls](./System_Calls/)
* [ ] [Signals](./Signals/)
* [ ] [Interrupts](./Interrupts/)
* [ ] [IPC](./IPC)

## TODO

* [ ] Memory management and layout
* [ ] Files, File Systems and Devices
* [ ] Linux Network Stack
* [ ] Semaphores, Mutexs, and CVs
* [ ] Data Structures
    * [ ] Doubly Linked List
    * [ ] Radix Tree
    * [ ] Bit Arrays
* [ ] Appendix
    * [X] [GDB](./Appendix/GDB)
    * [ ] [BASH](./Appendix/Shell/)
    * [ ] [Makefiles](./Appendix/Makefiles/)
    * [ ] [Linker Scripts](./Appendix/Linker_Scripts/)
    * [ ] [Linux Kernel Interfaces](./Appendix/Linux%20Kernel%20Interfaces/)
        * [ ] Sysfs
        * [X] [Procfs](./Appendix/Linux%20Kernel%20Interfaces/ProcFS/)
        * [ ] ioctl
    * [ ] Linux Services.
        
# Pre-Reqs

* Basic C and Linux Skills
* Warm and Fuzzy for IO, files, process memory foot print, etc.
* Linux System
* Basic understanding is needed for the following. We cover what is needed as we go and provide an [appendix](./Appendix) for quick reference on these topics.
    * GDB
    * Makefiles
    * Shell Scripting
