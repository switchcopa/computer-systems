	.file	"problem-3-13.c"
	.text
	.p2align 4
	.globl	comp_A
	.type	comp_A, @function
comp_A:
.LFB0:
	.cfi_startproc
	xorl	%eax, %eax
	cmpl	%esi, %edi
	setl	%al
	ret
	.cfi_endproc
.LFE0:
	.size	comp_A, .-comp_A
	.p2align 4
	.globl	comp_B
	.type	comp_B, @function
comp_B:
.LFB1:
	.cfi_startproc
	xorl	%eax, %eax
	cmpw	%si, %di
	setge	%al
	ret
	.cfi_endproc
.LFE1:
	.size	comp_B, .-comp_B
	.p2align 4
	.globl	comp_C
	.type	comp_C, @function
comp_C:
.LFB2:
	.cfi_startproc
	xorl	%eax, %eax
	cmpb	%dil, %sil
	setnb	%al
	ret
	.cfi_endproc
.LFE2:
	.size	comp_C, .-comp_C
	.p2align 4
	.globl	comp_D_0
	.type	comp_D_0, @function
comp_D_0:
.LFB3:
	.cfi_startproc
	xorl	%eax, %eax
	cmpq	%rsi, %rdi
	setne	%al
	ret
	.cfi_endproc
.LFE3:
	.size	comp_D_0, .-comp_D_0
	.p2align 4
	.globl	comp_D_1
	.type	comp_D_1, @function
comp_D_1:
.LFB4:
	.cfi_startproc
	xorl	%eax, %eax
	cmpq	%rsi, %rdi
	setne	%al
	ret
	.cfi_endproc
.LFE4:
	.size	comp_D_1, .-comp_D_1
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
