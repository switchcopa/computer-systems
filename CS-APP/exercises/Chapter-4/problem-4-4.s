
/*
Practice Problem 4.4 (solution page 518)
Write Y86-64 code to implement a recursive product function rproduct, based
on the following C code: (look at rproduct.c)

Use the same argument passing and register saving conventions as x86-64 code
does. You might find it helpful to compile the C code on an x86-64 machine and
then translate the instructions to Y86-64. */

/* Test this code in the online Y86-64 JS Simulator */

    .pos 0x0
    irmovq  stack, %rsp
    call main
    halt

    .align 8
array:  
    .quad 0x000000000001
    .quad 0x000000000002
    .quad 0x000000000003
    .quad 0x000000000004

main:
    irmovq  array, %rdi
    irmovq  $4, %rsi
    call rproduct
    ret

rproduct:
    mrmovq  (%rdi), %rax
    rrmovq  %rsi, %rdx
    iaddq   $-1, %rdx
    jle return

	pushq	%rbp
	rrmovq	%rsp, %rbp
    pushq   %rbx
	iaddq	$-8, %rsp
	mrmovq	(%rdi), %rbx
	iaddq	$-1, %rsi
	iaddq	$8, %rdi
	call rproduct
    rrmovq  %rbx, %rdi
    rrmovq  %rax, %rsi
    call imulq
    mrmovq  -8(%rbp), %rbx
    rrmovq  %rbp, %rsp
    popq    %rbp
return:
    ret

imulq:
    irmovq  $1, %r8
    xorq    %rdx, %rdx

    xorq    %rax, %rax
    subq    %rdi, %rax
    xorq    %rcx, %rcx
    subq    %rsi, %rcx
    andq    %rdi, %rdi
    jge L0
    rrmovq    %rax, %rdi
    xorq    %r8, %rdx
L0:
    andq    %rsi, %rsi
    jge L1
    rrmovq    %rcx, %rsi
    xorq    %r8, %rdx
L1:
    xorq    %rax, %rax
    xorq    %rcx, %rcx
loop:
    rrmovq  %rsi, %r9
    subq    %rcx, %r9
    jle end

    addq    %rdi, %rax
    iaddq   $1, %rcx
    jmp loop
end:
    xorq    %rdi, %rdi
    subq    %rax, %rdi
    andq    %rdx, %rdx
    cmovne  %rdi, %rax
    ret

    .pos 0xf00
stack:
