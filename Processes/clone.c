#include "lib_meme.h"

// #include <sched.h> -> Flags?
// long clone(unsigned long flags, void *stack,
//                     int *parent_tid, int *child_tid,
//                     unsigned long tls);

void _start()
{
    s32 tid = meme_gettid();
    meme_print_key_val_line("Parent TID", 10, 20, tid);

    s32 pid = meme_getpid();
    meme_print_key_val_line("Parent PID", 10, 20, pid);

    u32 mapped_mem_size = u32;
    void* mapped_mem = meme_mmap(NULL, 1024*1024, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(mapped_mem == (void*) -1)
    {
        meme_puts("MMAP FAILED!\n", 13);
        meme_exit(1);
    }

    u32 i = 0;
    for(; i < mapped_mem_size; ++i)
    {
        mapped_mem[0] = 0;
    }

    if(meme_munmap(mapped_mem, mapped_mem_size) < 0)
    {
        meme_puts("MUMAP FAILED!\n", 13);
        meme_exit(1);
    }

    meme_exit(0);
}