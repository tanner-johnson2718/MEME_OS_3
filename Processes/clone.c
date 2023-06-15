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

    meme_exit(0);
}