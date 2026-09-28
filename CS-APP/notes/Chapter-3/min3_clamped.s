	.file	"min3_clamped.c"
	.text
	.p2align 4
	.globl	min3_clamped
	.type	min3_clamped, @function
min3_clamped:
.LFB0:
	.cfi_startproc
	cmpl	%edx, %esi
	movl	%ecx, %eax
	cmovg	%edx, %esi
	cmpl	%edi, %esi
	cmovg	%edi, %esi
	cmpl	%ecx, %esi
	cmovge	%esi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	min3_clamped, .-min3_clamped
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
