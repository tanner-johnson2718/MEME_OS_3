#define _GNU_SOURCE
#include <sched.h>
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <signal.h>

///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////
int flags = SIGCHLD | CLONE_NEWPID;
int stack_size = 1024*1024;
int _idx = 0;

///////////////////////////////////////////////////////////////////////////////
// ID Shit
///////////////////////////////////////////////////////////////////////////////

typedef struct _id_t
{
    pid_t pid;
    pid_t ppid;
    pid_t pgid;
    pid_t tid;
} ids_t;

void pull_ids(ids_t* ids)
{
    ids->pid = getpid();
    ids->ppid = getppid();
    ids->pgid = getpgid(0);
    ids->tid = syscall(SYS_gettid);
}

void print_ids(char* name)
{
    ids_t ids;
    pull_ids(&ids);
    printf("========== %s ==========\n", name);
    printf("PID = %d\n", ids.pid);
    printf("PPID = %d\n", ids.ppid);
    printf("PGID = %d\n", ids.pgid);
    printf("TID = %d\n\n", ids.tid);
}

///////////////////////////////////////////////////////////////////////////////
// Thread Func
///////////////////////////////////////////////////////////////////////////////

int f(void* in)
{
    int idx = *((int*) in);

    print_ids("Child Init");

    pid_t sub1_pid = fork();
    if(sub1_pid == 0)
    {
        print_ids("Sub 1");
        pid_t sub2_pid = fork();
        if(sub2_pid == 0)
        {
            
            // kill parent and wait
            print_ids("Sub 2 b4 murder");
            kill(getppid(), 9);
            print_ids("Sub 2 after murder");

            while(getppid() != 1)
            {
                sleep(1);
            }

            exit(0);
        }   

        waitpid(sub2_pid, NULL, 0);
        exit(0);
    }

    if(waitpid(sub1_pid, NULL, 0) < 0)
    {
        printf("Waitpid FAILED\n");
    }
    printf("Sub 1 Died\n");
    if(waitpid(-1, NULL, 0) < 0)
    {
        printf("Waitpid FAILED\n");
    }
    printf("sub2 died\n");

    
    
    printf("Child Init Exiting\n");
}

///////////////////////////////////////////////////////////////////////////////
// Parent
///////////////////////////////////////////////////////////////////////////////

int main()
{

    print_ids("Parent");

    void* child_stack = malloc(stack_size);
    int child_tid = clone(&f, child_stack + stack_size, flags ,&_idx);
    if(child_tid < 0)
    {
        printf("CLONE FAILED\n");
        return 1;
    }

    waitpid(child_tid, NULL, 0);
    free(child_stack);
    printf("Parent Exiting\n");

    return 0;
}