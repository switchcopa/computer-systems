
/*
Practice Problem 3.24 (solution page 371)
For C code having the general form
*/

long loop_while(long a, long b) 
{
    long result = 0;
    while (a > b) {
        result = result + a * b;
        a = a - 1;
    }

    return result;
}

/*
I noticed it did:

leaq (, %rsi, %rdi), %rdx # ???
The lea instruction expects expects a constant for the scale
and the constant should be in {1, 2, 4, 8} because the CPU
does not use the ALU, but rather the Address Generation Unit.
The AGU's purpose is solely to calculate addresses to access
arrays, and the x86-64 architecture encodes that scale as a
2-bit integer, and performs a power of 2 to get that scale,
for example:

leaq  (%rsi, %rdi, 2), %rsi

here, the scale is encoded as the bits 01_2 = 1_10, and so
2^1 = 2, and we get the scale.
I should just change that with a imulq instruction instead.

gcc, run with command-line option -Og, produces the following code:

loop_while:
    xorl %eax, %eax
    jmp .L3
.L2:
    movq %rsi, %rdx
    imulq %rdi, %rdx
    addq  %rdx, %rax
    leaq -1(%rdi), %rdi
.L3:
    cmpq %rsi, %rdi
    jg .L2
    rep; ret
*/
