	.file	"integer-overflow-UB.c"
	.text
	.p2align 4
	.globl	does_overflow
	.type	does_overflow, @function
does_overflow:
.LFB3:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	does_overflow, .-does_overflow
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	movl	$2147483647, -4(%rsp)
	movl	-4(%rsp), %eax
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (GNU) 16.1.1 20260625"
	.section	.note.GNU-stack,"",@progbits
