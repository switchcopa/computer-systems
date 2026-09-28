	.file	"gfun.c"
	.text
	.p2align 4
	.globl	gfun
	.type	gfun, @function
gfun:
.LFB0:
	.cfi_startproc
	movslq	%edi, %rdi
	movslq	%esi, %rsi
	leaq	(%rdi,%rsi), %rax
	ret
	.cfi_endproc
.LFE0:
	.size	gfun, .-gfun
	.ident	"GCC: (GNU) 16.1.1 20260728"
	.section	.note.GNU-stack,"",@progbits
