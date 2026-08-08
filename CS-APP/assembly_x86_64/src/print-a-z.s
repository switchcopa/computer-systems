
.global _start
.section .text
_start:
    /* p = 32(%rsp), arr = (%rsp) */
    subq    $32, %rsp
    movq    %rsp, %rax
    movb    $'a, %cl
.L0:
    cmpb    $'z, %cl
    jg .L1

    movb    %cl, (%rax)
    incq    %rax
    incb    %cl
    jmp .L0
.L1:
    movb    $'\n, (%rax)
    incq    %rax
    movb    $0, (%rax)
    
    movq    $1, %rax
    movq    $1, %rdi
    movq    %rsp, %rsi
    movq    $27, %rdx
    syscall
    
    addq    $32, %rsp
    movq    $60, %rax
    movq    $0, %rdi
    syscall
