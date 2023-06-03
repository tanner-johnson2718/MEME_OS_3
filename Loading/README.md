# Hello World, What do you do?

In this installment we want figure out the exact process by which we go from typing the command `./hello` to our assembly code executing on the processor. As we saw in [dynamic linking](../Dynamic_Linking/), the dynamic linker is executed either prior to our programs execution or even during our programs exeutions. Also as we saw in our first [hello world](../Hello_World/) exploration, a basic hello world that uses the C standard library has several other functions and start up proedures than first meets the eye. Our Goal in this installment is to figure these start up procedures. Specifically we will cover:

* Command Line Arguments and Environment Variables
* Return Codes
* The shell
* All those extra functions called in our elf
* Loader vs Linker?


## Command Line Args and Environment Variables

