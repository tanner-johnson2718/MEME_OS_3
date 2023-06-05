#ifndef __MEME_LIB__
#define __MEME_LIB__

#define u64 unsigned long
#define u32 unsigned int
#define  u8 unsigned char
#define s64 long
#define s32 int
#define  s8 char

#define STD_IN_FD 0
#define STD_OUT_FD 1
#define STD_ERR_FD 2

#define NULL 0

// Calls syscall indicated by syscall number. Limit to 3 args (may need to
// expand later for syscalls that take more params). Uses generic unsigned 64
// bit value. Take care when casting return values and func args
u64 meme_generic_syscall3(u64 arg1, u64 arg2, u64 arg3, u64 syscall_num);

// Wrappers for commonly used syscalls
s32 meme_read(u32 fd, void* buff, u32 count);
s32 meme_write(u32 fd, void* buff, u32 count);
s32 meme_getpid(void);
s32 meme_getppid(void);
s32 meme_puts(u8* str, u32 len);
void meme_exit(s32 stat);
s32 meme_fork(void);
s32 meme_waitpid(s32 pid, s32* wstatus, s32 options);

u8 val_to_ascii(u64 in);
u32 ptr_to_hex_str(u64 ptr, u8* out, u32 out_size);

#endif