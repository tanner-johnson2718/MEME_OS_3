#include "lib_meme.h"

#define n_threads 1
void* stack_list[n_threads];
s32 parent_tid = -1; 
s32 thread_tids[n_threads];
const u32 stack_size = 1024*1024;

// Use same Clone flags as pthread create
const u64 clone_flags = CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES;

void f(void){
    meme_puts("here?\n", 6);
}

void _start()
{
    // Map mem for thread stacks
    int i;
    for(i = 0; i < n_threads; ++i)
    {
        stack_list[i] = meme_mmap(NULL, stack_size, PROT_READ|PROT_WRITE, MAP_STACK | MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
        meme_print_key_val_line("STACK", 5, 10, (u64) stack_list[i]);
        if((s64) stack_list[i] < 0l)
        {
            meme_puts("MMAP FAILED!\n", 13);
            meme_exit(1);
        }
    }
    
    // Spawn threads
    for(i = 0; i < n_threads; ++i)
    {
        s64 ret_tid = meme_clone(clone_flags, stack_list[i] + stack_size -1, &parent_tid, 
                            &thread_tids[i], (u64) f);

        meme_print_key_val_line("Ret", 3, 5, ret_tid);
    }

    // Clean Stacks
    for(i = 0; i < n_threads; ++i)
    {
        if(meme_munmap(stack_list[i], stack_size) < 0)
        {
            meme_puts("MUMAP FAILED!\n", 13);
            meme_exit(1);
        }
    }
    

    meme_exit(0);
}