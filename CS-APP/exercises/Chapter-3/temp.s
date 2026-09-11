	.file	"min3_clamped.c"
    .text
    .p2align 4
    .globl  min3_clamped
    .type   min3_clamped, @function
min3_clamped:
.LFB0:
    .cfi_startproc
    movl    %edi, %r8d
    cmpl    %edi, %esi
    cmovl   %esi, %r8d
    movl    %r8d, %r9d
    cmpl    %r8d, %edx
    cmovle  %edx, %r9d
    movl    %r9d, %eax
    cmpl    %r9d, %ecx
    cmovg   %ecx, %eax
    ret
    .cfi_endproc
.LFE0:
    .size	min3_clamped, .-min3_clamped
	.ident	"NOT GCC: (NGCC) 240.67 2067"
