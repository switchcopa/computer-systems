

# Y86-64 PROGRAM TO COMPUTE THE FLOOR OF THE
#  SQUARE ROOT OF A POSITIVE INTEGER 
#  floor_sqrt RETURNS -1 ON ERROR AND
#  floor(sqrt(n)) ON SUCCESS

    .pos 0x0
    irmovq  stack, %rsp
    call main
    halt

main:
    irmovq  $54, %rdi
    call floor_sqrt
    ret

floor_sqrt:
    irmovq  $1, %rax
    subq    %rdi, %rax
    cmovge  %rdi, %rax
    jge exit
    xorq    %rax, %rax
    irmovq  $1, %rdx
    irmovq  $1, %rcx
loop:
    iaddq   $2, %rdx
    iaddq   $1, %rax
    addq    %rdx, %rcx
    rrmovq  %rcx, %rsi
    subq    %rdi, %rsi
    jl loop
exit:
    ret

    .pos 0xf00
stack:

