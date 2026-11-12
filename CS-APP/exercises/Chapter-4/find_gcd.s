
/* Y86-64 Program to find the greatest
   common divisor between two positive
   integers
*/
    .pos 0x0
    irmovq  stack, %rsp
    call main
    halt

main:
    irmovq  $9, %rdi
    irmovq  $3, %rsi
    call gcd
    ret

gcd:
    pushq   %rbx # divident
    pushq   %rbp # last non-zero remainder
    rrmovq  %rdi, %rbx
    rrmovq  %rsi, %rbp
loop:
    rrmovq  %rbx, %rdi
    rrmovq  %rbp, %rsi
    call remainder
    andq    %rax, %rax
    je exit
    rrmovq  %rbp, %rbx
    rrmovq  %rax, %rbp
    jmp loop
exit:
    rrmovq  %rbp, %rax
    popq    %rbp
    popq    %rbx
    ret

remainder:
    andq    %rdi, %rdi
    je L2
    andq    %rsi, %rsi
    je L2
    rrmovq  %rdi, %rdx
    rrmovq  %rdi, %rax
    subq    %rsi, %rax
    cmovle  %rsi, %rdi
    cmovle  %rdx, %rsi
    rrmovq  %rsi, %rdx
    jmp L1
L0:
    rrmovq  %rdx, %r8
    addq    %rsi, %rdx
L1:
    rrmovq  %rdi, %rax
    subq    %rdx, %rax
    jg L0
    rrmovq  %r8, %rdx
    subq    %rdx, %rdi
    rrmovq  %rdi, %rax
    subq    %rax, %rsi
    cmove   %rsi, %rax
L2:
    ret

    .pos 0xf00
stack:

