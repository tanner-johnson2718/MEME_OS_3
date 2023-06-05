# Hello World, What do you do?

In this installment we want figure out the exact process by which we go from typing the command `./hello` to our assembly code executing on the processor. As we saw in [dynamic linking](../Dynamic_Linking/), the dynamic linker is executed either prior to our programs execution or even during our programs exeutions. Also as we saw in our first [hello world](../Hello_World/) exploration, a basic hello world that uses the C standard library has several other functions and start up proedures than first meets the eye. Our Goal in this installment is to figure what is going on with these start up procedures. Specifically we will cover:

* Command Line Arguments and Environment Variables
* Return Codes
* The shell
* Libc and Dynamic Linker Invocation


## Command Line Args and Environment Variables

In `cmd_args.c` we write a small program to output the contents and locations of the command line args and evironment variables relative to the main stack frame. Running this we can gather a few interesting things that one may not have been aware of prior

* First note the non standard signature: `int main(int argc, char** argv, char** envp)`.
    * Most only use thd first two arguments to main, however environment variables can also be accessed via a 3rd main argument.
    * They can also be accessed via the C standard library global `environ`.
* The environment variables of the shell used to execute the program are loaded into the memory of the program. Specifically the stack.
    * Using proc/<pid>/maps we can see that these are stored at the very very top of the memory region allocated for the stack. 
* The command line args are also stored at the very top of the stack
* This gives us the following stack layout per [CSAPP](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf) :

![alt text](./cmd_args.png)

This leads to an important question, **who exactly is responisble for setting up the stack with these environment variables and command line args?** We can determine if it is the C standard library by writing a C program that is compiled with the `-nostdlib` flag and exploring its stack space. We create a C program called `no_lib.c `. Its compiled with `gcc -nostdlib -static  -fno-asynchronous-unwind-tables -o no_lib no_lib.c`. Now we use gdb to explore its stack space.

* `gdb no_lib`
* `b _start`
* `r`
* `info inferiors` to get pid
* Use `cat /proc/<pid>/maps` to see mem segments
    * we can see top of stack is at `0x7ffffffff000`
* `info reg` shows `rsp = 0x7fffffffe000` a full 0x1000 off from allocated stack memory segment.
* If we start examining memory we see we get the exact layout as shown in the image above. Only difference is now our `_start` stack frame is directly beneath the start of the argv and envp arrays and strings.

Thus this leads to the question, **who or what exactly is creating this stack memory segment and who is copying the env and cmd line arguments onto the stack memory segment?** We will explore this later in this installment. But as we've seen command line arguments are accessible because they copied by something into our programs stack memory.

## Return Codes

Return or exit codes are concept used to tell whether a program executed successfully or not. Its mechanism is pretty simply and is arbitraited by system calls. The `exit` system call allows a process to indicate to its parent what its exit code is, and this is returned to the parent via the `waitpid` system call. These exit codes are heavily relied on by the unix shell. This all will make more sense once we cover processess and if one reads the Bash Shell appendix entry. However for now, the key take away is that return codes or exit codes are implemented via system calls.

## The Shell and Launching a Program

We are not gonna look at how new processes are created on Linux at this moment. We will cover processes in much more detail later. But the creation of a process is going to shed light on our current topic, loading programs. All processes are created by "forking" or duplicating an existing process. This copies just about everything in the current process and duplicates in the second "child" process. Again we will cover this in more detail, but that is what fork is at its essence. The Exec family of system calls replaces the current process image with that of the new one specified in its arguments. As we will see, it is this system call that sets up the stack with the command line args and the environment variables.

This fork, exec combo is how the shell launches your program. While the shell does much more than this, at the end of the day when you type `./my_prog`, the shell process forks and calls exec on your passed program. Since all of this outside of our current scope and will be covered in detail later, we shall answer our above question simply and leave it for later study. That is, who is creating the stack memory and copying command line args to it? Exec.

## Libc and Dynamic Linker Invocation

We are leaving exploring process creation to our study of process later. Thus we will conclude this section by looking at what happens to a hello world, using the C standard library, when it is ran. Specifically we will start our study when the memory of the process is set up and the instruction pointer pointing to the first instruction as specified by the start point in the ELF header.

![alt text](./callgraph.png)

The above call graph gives us an idea of what to look for as we reverse engineer our hello world:

```C
#include <stdio.h>

int main()
{
    printf("Hello\n");
    return 0;
}
```

We will dig into the loading of this by using GDb. If we start executing at the very first instruction we see that we find ourself in the _start function of the dynamic linker (ld-linux-x86-64.so.2). Skipping through the execution of the dynamic linker and looking at the GOT before and after we get the table below. We can see from this that dynamic linker chose not to do lazy binding and the required symbols were linked prior to the dynamic linker passing control to our exe.

| .got Addr | Symbol | Val before linker | Val after |
| --- | --- | --- | --- |
| 0x555555557fb8 | .dynamic | 0x3dc8 | 0x3dc8 |
| 0x555555557fc0 | dynamic reloc entries | 0x0 | 0x0 |
| 0x555555557fc8 | dynamic linker | 0x0 | 0x0 |
| 0x555555557fd0 | puts | 0x1030 | 0x7ffff7e2f4 |
| 0x555555557fd8 | _ITM_deregisterTMCloneTable | 0x0 | 0x0 |
| 0x555555557fe0 | __libc_start_main | 0x0 | 0x7ffff7dcef90 |
| 0x555555557fe8 | __gmon_start_ | 0x0 | 0x0 |
| 0x555555557ff0 | _ITM_registerTMCloneTable | 0x0 | 0x0 |
| 0x555555557ff8 | __cxa_finalize | 0x0 | 0x7ffff7df1f10 |

Using GDB and objdump we can see that the compiler made our entry point for us. The _start function


* _start in our hello
* __lib_start_main
* __libc_csu_init
* _init
* frame_dummy
* register_tm_clones
* __libc_csu_init
* __lib_start_main
* main
* __lib_start_main
* __cxa_finalize
* deregister_tm_clones