# MEME OS 3

In the first installment of MEME OS we built a virtual linux OS using build root, customized the kernel, and linked a GDB debugger to the kernel while executing in QEMU. In MEME OS 2 we created a bare bones OS and some bare metal drivers again targeting QEMU.

MEME OS 3 will take a bit of a detour. The eleavator pitch is "everything your 4000 level OS Comp Sci class should have been". This project will be an exploration of a linux system running on actual hardware. We will treat our linux system as object of study. Starting from a hello world, we will look at:

* What does `#include <stdio.h>` do **exactly**?
    * Where are the definitions and declarations of libraries inlcude like this?
* Why is entry function `int main(..)`?
    * How are args passed?
    * Exit Codes?
    * Execution?
* ... etc ...

We will repeat this type of questioning and digging for increasingly complicated boiler plate C and linux code. The goal here being make precise and rigorious the exact system processes we take for granted while programming and use this type of "playing" or "exploring" as a mechanism for understanding how linux works.

To keep projected well bounded we will implace the following contraints)

* Only look at what can be gathered from user space C programs, command line tools, and system interfaces. (Still include references to kernel code or headers but focus on what can be seen / interfaced with via a terminal or C program in user land).
* Use a singular program as a means to examine a small set of topics. 

# Road Map

* [ ] Hello World
* [ ] Stack Space Exploration (Local Variable Declaration)
* [ ] Heap Exploration (Malloc)
* [ ] File IO
* [ ] Sockets
* [ ] Forks, Process CTL

# Pre-Reqs

* Basic C and Linux Skills
* Warm and Fuzzy for IO, files, process memory foot print, etc.
* Linux System
    * 
* GDB 