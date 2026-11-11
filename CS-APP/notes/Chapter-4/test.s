
.pos 0x1000
    .quad 0x1
    .quad 0x2
    .quad 0x3
    .quad 0x4

.pos 0x0
main:
    irmovq  $0xF000, %rsp
    irmovq  $0x1000, %rdi
    irmovq  $4, %rsi
    call double_elements
    xorq    %rax, %rax
    ret

double_elements:
    xorq    %rax, %rax
    subq    %rax, %rsi
    je exit
    irmovq  $1, %r11
    irmovq  $8, %r8
    xorq    %r9, %r9
    rrmovq  %rdi, %rdx
loop:
    mrmovq  (%rdx), %rcx
    addq    %rcx, %rcx
    rmmovq  %rcx, (%rdx)
    addq    %r8, %rdx
    addq    %r11, %r9
    rrmovq  %rsi, %r10
    subq    %r9, %r10
    jg loop
exit:
    ret
