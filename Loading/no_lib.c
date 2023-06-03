// C program with no std library. Find the top of the stack frame of the start
// function, then use procfs to see how much memory is in between that and the
// end of the stack allocated memory segment.

// Easiest way to do this is a nop start and use gdb

void _start()
{
    asm(
        "nop\n"
    );
}