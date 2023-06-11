#include "lib_meme.h"

void _start()
{
    const u32 iters = 0;
    const u32 sleep_time = 1;

    if(iters > 0)
    {
        int i, j;
        for(i = 0; i < iters; ++i)
        {
            j += i;
        }
    }
    
    if(sleep_time > 0)
    {
        meme_alarm(sleep_time);
        meme_pause();
    }

    struct rusage ruse = {0};

    s32 ret = meme_getrusage(RUSAGE_SELF, &ruse);
    if(ret < 0)
    {
        meme_puts("RUSAGE FAILED, OH NO!", 21);
        meme_exit(1);
    }

    u32 pad = 25;

    meme_print_key_val_line("user cpu sec", 12, pad, ruse.ru_utime.tv_sec);
    meme_print_key_val_line("user cpu usec", 13, pad, ruse.ru_utime.tv_usec);
    meme_print_key_val_line("system cpu sec", 14, pad, ruse.ru_stime.tv_sec);
    meme_print_key_val_line("system cpu usec", 15, pad, ruse.ru_stime.tv_usec);
    meme_print_key_val_line("Max RSS", 7, pad, ruse.ru_maxrss);
    meme_print_key_val_line("None IO Page Faults", 19, pad, ruse.ru_minflt);
    meme_print_key_val_line("Page Faults", 11, pad, ruse.ru_majflt);
    meme_print_key_val_line("# File Input", 12, pad, ruse.ru_inblock);
    meme_print_key_val_line("# File Output", 13, pad, ruse.ru_oublock);
    meme_print_key_val_line("Vol. Context Switch", 19, pad, ruse.ru_nvcsw);
    meme_print_key_val_line("Forced Contect Switch", 21, pad, ruse.ru_nivcsw);

    meme_exit(0);
}
