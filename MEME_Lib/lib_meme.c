#include "lib_meme.h"

// ============================================================================
// Sys Calls
// ============================================================================
u64 meme_generic_syscall3(u64 arg1, u64 arg2, u64 arg3, u64 syscall_num)
{
    asm(
        "mov %rcx, %rax\n"
        "syscall\n"
    );
}

s32 meme_read(u32 fd, void* buff, u32 count)
{
   asm(
        "mov $0,%rax\n"
        "syscall\n"
   );
}

s32 meme_write(u32 fd, void* buff, u32 count)
{
    asm(
        "mov $1,%rax\n"
        "syscall\n"
   );
}

s32 meme_getpid(void)
{
    asm(
        "mov $39,%rax\n"
        "syscall\n"
   );
}

s32 meme_getppid(void)
{
    asm(
        "mov $110,%rax\n"
        "syscall\n"
   );
}

void meme_exit(s32 stat)
{
    asm(
        "mov $60,%rax\n"
        "syscall\n"
   );
}

s32 meme_puts(u8* str, u32 len)
{
    meme_write(1, str, len);
}

s32 meme_fork(void)
{
    asm(
        "mov $57,%rax\n"
        "syscall\n"
   );
}

s32 meme_waitpid(s32 pid, s32* wstatus, s32 options)
{
    asm(
        "mov $61,%rax\n"
        "mov $0, %r10\n"
        "syscall\n"
   );
}


// ============================================================================
// String Manip
// ============================================================================

// Take in a u64 and convert it to its ascii value.
u8 val_to_ascii(u64 in)
{
    if(in < 10ul)
    {
        return (u8) (in + '0');     // 48 = ascii('0')
    }

    // 97 = ascii('a'). Subtract 10 so that 10 -> 'a'.
    return (char) (in -10ul + 'a');          
}

// Convert the ptr to a hex ascii string. Return number of byte written. If out
// str is not big enough, then simply write as much as we can until full.
u32 ptr_to_hex_str(u64 ptr, u8* out, u32 out_size)
{

    u64 temp[16];
    u32 ctr = 0;

    // Mod it 16 to find lowest digit. Divide by 16 then mod again to find next
    // lowest digit. Loop this until we get 0;
    while(ptr != 0ul && ctr < 16)
    {
        temp[ctr] = ptr % 16ul;
        ptr = ptr >> 4;             // Faster div by 16
        ctr++;
    }

    if(out_size >= 2)
    {
        out[0] = '0';
        out[1] = 'x';
    }
    else
    {
        return 0;
    }
    

    u32 i;
    for(i = 0; (i < ctr) && ((i+2) < (out_size -1)); ++i)
    {
        out[2+i] = val_to_ascii(temp[ctr-1-i]);
    }

    out[2 + i] = 0;

    return 3+i;
}