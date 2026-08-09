	.file	"print-a-z-C.c"
	.text
	.globl	_start
	.type	_start, @function
_start:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	-64(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	$28, -24(%rbp)
	movb	$97, -9(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	-9(%rbp), %edx
	movb	%dl, (%rax)
	movzbl	-9(%rbp), %eax
	addl	$1, %eax
	movb	%al, -9(%rbp)
.L2:
	cmpb	$122, -9(%rbp)
	jle	.L3
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movb	$10, (%rax)
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
	leaq	-64(%rbp), %rcx
	movq	-24(%rbp), %r8
#APP
# 13 "print-a-z-C.c" 1
	movq   $1, %rax
	movq   $1, %rdi
	movq   %rcx, %rsi
	movq   %r8, %rdx
	syscall
# 0 "" 2
# 25 "print-a-z-C.c" 1
	movq   $60, %rax
	movq   $0, %rdi
	syscall
# 0 "" 2
#NO_APP
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_start, .-_start
	.ident	"GCC: (GNU) 16.1.1 20260728"
	.section	.note.GNU-stack,"",@progbits
