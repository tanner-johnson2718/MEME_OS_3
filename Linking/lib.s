	.file	"lib.c"
	.text
	.globl	string_ptr
	.section	.rodata
.LC0:
	.string	"Hello"
	.section	.data.rel.local,"aw"
	.align 8
	.type	string_ptr, @object
	.size	string_ptr, 8
string_ptr:
	.quad	.LC0
	.text
	.globl	get_str
	.type	get_str, @function
get_str:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	string_ptr(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	get_str, .-get_str
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
