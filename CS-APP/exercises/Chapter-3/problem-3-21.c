
/*
Practice Problem 3.21 (solution page 369)
Starting with C code of the form
*/
short test(short x, short y) {
    short val = y + 12;
    if (x < 0) {
        if (x < y)
            val = x * y;
        else
            val = x | y;
    } else if (y >= 10)
        val = x / y;
    return val;
}

/*
gcc generates the following assembly code:

test:
    leaq    12(%rsi), %rbx
    testq   %rdi, %rdi
    jge .L2
    movq    %rdi, %rbx
    imulq   %rsi, %rbx
    movq    %rdi, %rdx
    orq     %rsi, %rdx
    cmpq    %rsi, %rdi
    cmovge  %rdx, %rbx
    ret
.L2:
    idivq   %rsi, %rdi
    cmpq    $10, %rsi
    cmovge  %rdi, %rbx
    ret

Fill in the missing expressions in the C code.
*/
