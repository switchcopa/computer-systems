
    .pos 0x0
    irmovq  stack, %rsp
    call main
    halt

    .align 16
array:
    .quad 0x4a7c8b2f1e3d9012
    .quad 0xdeadbeefcafebabe
    .quad 0x0123456789abcdef
    .quad 0x89abcdef01234567
    .quad 0x7f3a2b1c0e9d8f47
    .quad 0xffeeddccbbaa9988
    .quad 0x9a8b7c6d5e4f3a21
    .quad 0x1122334455667788

main:
    irmovq  array, %rdi
    irmovq  $8, %rsi
    call max
    ret

max:
    andq    %rsi, %rsi
    jle exit
    mrmovq  (%rdi), %rax
    iaddq   $8, %rdi
    xorq    %rcx, %rcx
loop:
    rrmovq  %rcx, %rdx
    subq    %rsi, %rdx
    jge exit
    mrmovq  (%rdi), %rdx
    rrmovq  %rdx, %r8
    subq    %rax, %r8
    cmovge  %rdx, %rax
    iaddq   $8, %rdi
    iaddq   $1, %rcx
    jmp loop
exit:
    ret

    .pos 0xf00
stack:
