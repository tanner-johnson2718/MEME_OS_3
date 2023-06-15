#include "lib_meme.h"

void _start()
{
    s32 tid = meme_gettid();
    meme_print_key_val_line("Parent TID", 10, 20, tid);

    s32 pid = meme_getpid();
    meme_print_key_val_line("Parent PID", 10, 20, pid);

    u32 mapped_mem_size = 1024*1024;
    void* mapped_mem = meme_mmap(NULL, mapped_mem_size, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if((s64) mapped_mem < 0l)
    {
        meme_puts("MMAP FAILED!\n", 13);
        meme_exit(1);
    }

    meme_print_key_val_line("MEM", 3, 20, mapped_mem);

    u32 i = 0;
    for(; i < mapped_mem_size; ++i)
    {
        ((char*) mapped_mem)[i] = 0;
    }


    

    if(meme_munmap(mapped_mem, mapped_mem_size) < 0)
    {
        meme_puts("MUMAP FAILED!\n", 13);
        meme_exit(1);
    }

    meme_exit(0);
}