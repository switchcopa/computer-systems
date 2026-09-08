	.file	"xorq.c"
	.text
	.p2align 4
	.globl	xorq
	.type	xorq, @function
xorq:
.LFB0:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	xorq, .-xorq
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
