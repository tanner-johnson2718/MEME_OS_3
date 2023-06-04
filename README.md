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

Here we will "tell the story" of this project. 

**Part 1**
We started with a simple hello world in C and this served as the boiler plate code that guided our exploration in part 1. Our very first question is: [what exactly is this output file](./Hello_World). This lead to a "bullet-pointy" overview of the ELF format and its contents. This in turn lead to several other questions. Much of the contents of an ELF are used in the process of linking so that was the second topic we looked at. We started with [static linking](./Linking) where we described how symbols are used to "export" and "import" the shared entities in a given C file to another. We also looked at relocation which how assembled C files are patched together so that references to symbols on other files are resolved. Static linking copies the code and data of assembled C files into every executable that uses said code and data. That's inefficient and [Dynamic Linking](./Dynamic_Linking) solves this issue. With dynamic linking we looked at how the PLT and GOT are used by the dynamic linker to resolve symbols at run time. Finally, we concluded our disection of the hello world by looking at how executables are [Loaded](./Loading) once its process is created. At the conclusion of Part 1, one should have a very good understanding about how one goes from a C hello world to an executable loaded in memory that uses system calls and references the C standard library to print "Hello" to the terminal.

**Part 2**
Part 2 is where we start to dig deeper into the kernel space. 

## Check List

* [X] [Hello World, What did you give me?](./Hello_World) (ELF File Format)
* [X] [Hello World, A link to the past](./Linking) (Static Linking and Archives)
* [X] [Hello World, Sharing is Caring](./Dynamic_Linking) (Dynamic Linking and Shared Libraries)
* [ ] [Hello World, What do you do?](./Loading) (Loading a Process)
* [ ] System Calls
* [ ] Interrupts
* [ ] Signals
* [ ] Processes and Threads
* [ ] Memory management and layout
* [ ] Files, File Systems and Devices
* [ ] Linux Network Stack
* [ ] Semaphores, Mutexs, and CVs
* [ ] Appendix
    * [ ] Makefiles
    * [ ] Linker Scripts
    * [ ] Sysfs, Procfs, and other System Interfaces
    * [ ] GDB, Valgrind, and other Tools

## Topic Graph

# Pre-Reqs

* Basic C and Linux Skills
* Warm and Fuzzy for IO, files, process memory foot print, etc.
* Linux System
* Basic understanding is needed for the following. We cover what is needed as we go and provide an [appendix](./Appendix) for quick reference on these topics.
    * GDB
    * Makefiles
    * Shell Scripting
