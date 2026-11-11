	.file	"rproduct.c"
	.text
	.globl	rproduct
	.type	rproduct, @function
rproduct:
	movl	$1, %eax
	cmpq	$1, %rsi
	jle	.L5
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%rbx
	subq	$8, %rsp
	movq	(%rdi), %rbx
	subq	$1, %rsi
	addq	$8, %rdi
	call	rproduct
	imulq	%rbx, %rax
	movq	-8(%rbp), %rbx
	leave
	ret
.L5:
	ret
	.size	rproduct, .-rproduct
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
