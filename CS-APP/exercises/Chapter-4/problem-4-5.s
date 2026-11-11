/*
Practice Problem 4.5 (solution page 519)
Modify the Y86-64 code for the sum function (Figure 4.6) to implement a function
absSum that computes the sum of absolute values of an array. Use a conditional
jump instruction within your inner loop. */

    .pos 0x0
    irmovq  stack, %rsp
    call main
    halt

    .align 8
array:
    .quad 0x0000000000000001
    .quad 0xfffffffffffffff0
    .quad 0xfffffffffffff4e9
    .quad 0x0000000000000043

main:
    irmovq  array, %rdi
    irmovq  $4, %rsi
    call abs_sum
    ret

abs_sum:
    xorq    %rax, %rax
    andq    %rsi, %rsi
    jmp test
loop:
    mrmovq  (%rdi), %rdx
    xorq    %rcx, %rcx
    subq    %rdx, %rcx
    andq    %rdx, %rdx
    cmovl   %rcx, %rdx
    addq    %rdx, %rax
    iaddq   $8, %rdi
    iaddq   $-1, %rsi
test:
    jne loop
    ret

    .pos 0xf00
stack:
