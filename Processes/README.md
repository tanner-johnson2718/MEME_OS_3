# Processes and Threads

In previous sections we looked at hello world and saw that our hello world PROGRAM gets encapuslated in the Linux concept of a process. This is what we shall look at here. At a high level a process is a "thread" of execution of a program that also has certain associated resources. These are:

* A Stack
* Virutal Memory
* Open Files
* Signal Handlers
* Etc

Processes are created in linux by copying or forking an existing process. All processes besides the init process have a single parent. Thus this makes the set of all processes on a system a tree. Processes have many relavent system calls and we will explore them in depth in this section. Some that we have already used are:

* Fork
* Clone
* Exec
* Waitpid
* Getpid
* Getppid
* Exit
* etc, etc

In this installment we want to take a fairly detailed look at Linux Processes, how thier created, manipulated, and what precisely a process is composed of.

# Process Creation and Manipulation

# Process Resources

# Process System Calls

# Questions

* struct rusage *ru in wait?

# Resources
* https://linux-kernel-labs.github.io/refs/heads/master/so2/lec3-processes.html
* https://tldp.org/LDP/tlk/kernel/processes.html
* [CSAPP CH 8](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)