
/*
Practice Problem 3.26 (solution page 372)
A function test_one has the following overall structure:
*/

long test_one(unsigned long x) {
    long val = 1;
    while (x > 0) {
        val = (val ^ x);
        x >>= 1;
    }

    return val & 1;
}

/*
The gcc C compiler generates the following assembly code:

test_one:
    movl $1, %eax
    jmp .L5
.L6:
    xorq %rdi, %rax
    shrq %rdi
.L5:
    testq %rdi, %rdi
    jne .L6
    andl $1, %eax
    ret

Reverse engineer the operation of this code and then do the following:
A. Determine what loop translation method was used.
B. Use the assembly-code version to fill in the missing parts of the C code.
C. Describe in English what this function computes.

A. Guarded do-loop.
C. This function computes whether the number of set bits in x is even (1)
or odd (0).
*/
