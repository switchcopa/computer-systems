
/*
CS:APP Practice Problem 3.31
Reconstruct the C code for the following function switcher.
*/

/* Dissassembly 
# a in %rdi, b in %rsi, c in %rdx, dest in %rcx
switcher:
    cmpq    $7, %rdi
    ja      .L2
    jmp     *.L4(,%rdi,8)

.L3:                        # Case A
    leaq    1(%rsi), %rax
    jmp     .L6

.L5:                        # Case B
    movq    %rsi, %rax
    addq    %rdx, %rax
    jmp     .L6

.L7:                        # Case C
    movq    $15, %rax
    jmp     .L6

.L2:                        # Default
    movq    %rsi, %rax

.L6:                        # Exit
    movq    %rax, (%rcx)
    ret

    .section    .rodata
    .align 8
.L4:
    .quad   .L3    # Index 0
    .quad   .L2    # Index 1
    .quad   .L5    # Index 2
    .quad   .L2    # Index 3
    .quad   .L7    # Index 4
    .quad   .L2    # Index 5
    .quad   .L5    # Index 6
    .quad   .L2    # Index 7
*/

void switcher(long a, long b, long c, long *dest) {
    long ret;
    switch (a) {
    case 0:
        ret = b + 1;
        break;
    case 2:
    case 6:
        ret = b + c;
        break;
    case 4:
        ret = 15;
        break;
    default:
        ret = b;
        break;
    }

    *dest = ret;
}
