	.file	"simple_l.s"
    .text
    .globl  simple_l
    .type   simple_l, @function
simple_l:
LFB0:
    pushl   %ebp
    movl    %esp, %ebp
    movl    8(%ebp), %edx
    movl    (%edx), %eax
    addl    12(%ebp), %eax
    movl    %eax, (%edx)
    leave
    ret
