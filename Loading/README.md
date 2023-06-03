# Hello World, What do you do?

In this installment we want figure out the exact process by which we go from typing the command `./hello` to our assembly code executing on the processor. As we saw in [dynamic linking](../Dynamic_Linking/), the dynamic linker is executed either prior to our programs execution or even during our programs exeutions. Also as we saw in our first [hello world](../Hello_World/) exploration, a basic hello world that uses the C standard library has several other functions and start up proedures than first meets the eye. Our Goal in this installment is to figure these start up procedures. Specifically we will cover:

* Command Line Arguments and Environment Variables
* Return Codes
* The shell
* All those extra functions called in our elf
* Loader vs Linker?


## Command Line Args and Environment Variables

In `cmd_args.c` we write a small program to output the contents and locations of the command line args and evironment variables relative to the main stack frame. Running this we can gather a few interesting things that one may not have been aware of prior

* The environment variables of the shell used to execute the program are loaded into the memory of the program
    * Using proc/<pid>/maps we can see that these are stored at the very very top of the memory region allocated for the stack. 
* The command line args are also stored at the very top of the stack
* This gives us the following stack layout per [CSAPP](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf) :

![alt text](./cmd_args.png)