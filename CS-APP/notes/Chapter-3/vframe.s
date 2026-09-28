
    .text
    .globl  vframe
vframe:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    leaq    22(, %rdi, 8), %rax
    andq    $-16, %rsp
    subq    %rax, %rsp
    leaq    7(%rsp), %rax
    shrq    $3, %rax
    leaq    0(, %rax, 8), %r8
    movq    %r8, %rcx
.L3:
    movq    %rdx, (%rcx, %rax, 8)
    addq    $1, %rax
    movq    %rax, -8(%rbp)
.L2:
    movq    -8(%rbp), %rax
    cmpq    %rdi, %rax
    jl .L3
    leave
    ret
