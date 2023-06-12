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
* wait4
* getpgid
* setpgid

In this installment we want to take a fairly detailed look at Linux Processes, how thier created, manipulated, and what precisely a process is composed of.

# Process Creation, Manipulation, and Execution

## Identifying and Grouping Processes

As we've seen and explained many times a process gets created by copying an existing process. It has a field called a `pid` that can be accesed via the `getpid` system call that uniquely identifies a process on the system. Processes also maintain a `ppid` field which gives the `pid` of its parent. These two identify where a process sits in the process tree and who owns that process.

Processes can also be grouped into a collection called ... well a group. By default the group ID of process launched is given a group ID = to its own pid. If this process then forks any children, that child inherits th group id of its paretn unless its parent or itself change its group ID. Note that if an exec call is used, the parent can no longer change the gid of its child. Group IDs exist so that process can be manipuled and communicated with in groups in stead of indivdually. In the file `proc.c` we give an example of how using these system calls work and how PIDs and GPIDs work.

In `proc.c` we create process tree with a parent that has two children and one of its own children also has a child. If `child1_in_own_grp = 0`, then all children belong to the same process group whose ID is that of the pid of the parent. Now if we set `child1_in_own_grp = 1`, then all children including the grand child get put into a process group whose ID is that of the first child. This case shows how we can move children into differnt groups to simplify book keeping

## Process State, Reaping, and Zombie Processes

Notice that in `proc.c` we make use of the `waitpid` system call. This system call waits until a process dies and allows us to get the exit status of our child process. `waitpid` can be used to wait for any child, a specific child, or even any child in a specific process group. The `waitpid` system call also has options for non blocking calls, returing if a child is stopped and not just terminated (more on this later), or has previously been stopped and is now resumed. Finally, the `waitpid` system call is actually implemented in libc. The actual underlying system call is `wait4`, which takes the exact same arguments as `waitpid` put has an additional pointed to a runtime usage struct that gives us some details about the processes excution. Again more on this later.

Now it turns out that `waitpid` is more that a control flow call and it is 100% fundamental to the cleaning up of a process. If one does not call `waitpid` on its child process, the child enters a state called being a "zombie". It is terminated but its in kernel data structure is still maintained in memory. The process of calling `waitpid` on a child process is called "reaping". If a parent exits and does not reap its child, this child becomes an orphan. Orphans will be adopted by the init process and a linux service will reap them periodically. `proc.c` shows the proper way to deal call `waitpid` on chidren so as to avoid making them an orphan.

Processes have a state associated with them and they move from state to state depending on their execution. This creates a state machine.

## Preemption and Context Switches

## Resources

* https://www.win.tue.nl/~aeb/linux/lk/lk-10.html
* https://linux-kernel-labs.github.io/refs/heads/master/so2/lec3-processes.html
* https://tldp.org/LDP/tlk/kernel/processes.html
* [CSAPP CH 8](../Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)

# Process Resources

The rusage struct gives us 

```C
struct rusage {
    struct timeval ru_utime; /* user CPU time used */
    struct timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};
```

# What are all these processes

## ps utility

# Proc-FS

* https://docs.kernel.org/filesystems/proc.html

# Questions

* struct rusage *ru in wait?
* What are these "sys/*" includes? Are the libc or system headers?

# Resources

