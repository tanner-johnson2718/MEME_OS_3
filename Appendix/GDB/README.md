# My GDB Cheat Sheet

Below is table of the must know GDB commands. With these you can almost examine almost anything in your process. We will add to this list as we examine more and more topics.

| Command | Description | Comment |
| --- | --- | --- |
| `starti` | Start executing at very first instruction | Usually Dynamic Linker _start function |
| `b <addr/symbol>` | Add break point at address or symbol | - |
| `ni` | Next instruction, stepping over function calls | - |
| `si` | Next instruction, stepping INTO function calls | - |
| `x/<N><f><u>` | N = Num units, f format i.e. x for hex, s for string, etc, u = unit. u almost always is g for 8 bytes. | - |
| `info inferiors` | Get PID | - | 
| `info proc mappings` | See Process Memory Mappings | - |
| `lay next` | Cycle default Layouts | - |
| `info files` | Section Address Mappings | Good for finding GOT, PLT, etc in process memory map |
| `info reg` | Print registers | - |
| `p $<reg>` | Print a specific register | Pretty output with symbol resoltion. Good for seeing stack pointers in particular |
| `info address <symbol>` | Print the address of a symbol | - |