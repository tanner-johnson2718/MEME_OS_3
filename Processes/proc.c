#include "lib_meme.h"
#include <wait.h>

void _start()
{
    s32 pid = meme_fork();
    if(pid == 0)
    {
        // child
        meme_puts("Child\n", 6);
        meme_exit(16);
    }

    // parent
    s32 stat = 0x69;
    u8 buff[16];
    s32 ret = meme_waitpid(pid, &stat, 0);
    if(ret != pid)
    {
        meme_puts("ERROR, waitpid, failed\n", 23);
        meme_exit(1);
    }
    meme_puts("Parent\n", 7);
    u32 len = ptr_to_hex_str((u64) WEXITSTATUS(stat), buff, 16);
    meme_puts("Stat = ", 7);
    meme_puts(buff, len-1);
    meme_puts("\n", 1);
    meme_exit(0);
}