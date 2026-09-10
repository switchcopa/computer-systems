/*
Practice Problem 3.23 (solution page 370)
For the C code
*/

long dw_loop(long x) {
    long y = x / 9;
    long *p = &x;
    long n = 4 * x;
    do {
        x += y;
        (*p) += 5;
        n -= 2;
    } while (n > 0);
    return x;
}

/*
gcc generates the following assembly code:

dw_loop:
    movq    %rdi, %rsi
    idivq   $9, %rsi
    leaq    (, %rdi, 4), %rcx
.L2:
    leaq    5(%rdi, %rsi), %rdi
    subq    $2, %rcx
    testq   %rcx, %rcx
    jg .L2
    movq    %rdi, %rax
    ret
    
A. Which registers are used to hold program values x, y, and n?
B. How has the compiler eliminated the need for pointer variable p and the
pointer dereferencing implied by the expression (*p)+=5?
C. Add annotations to the assembly code describing the operation of the pro-
gram, similar to those shown in Figure 3.19(c).
*/

/*
I saw that rbx is a callee-saved register, so I just replaced
it with %rsi
A. x = %rdi, y = %rsi, n = %rcx
B. Because it reasoned that since p always pointed to x, and
every memory reference of p directly changes x, then we could
just replace p with x.
C.

dw_loop:
    movq    %rdi, %rsi # y = x
    idivq   $9, %rsi # y /= 9
    leaq    (, %rdi, 4), %rcx # n = 0 + x * 4
.L2:
    leaq    5(%rdi, %rsi), %rdi # x = x + y + 5
    subq    $2, %rcx # n = n - 2
    testq   %rcx, %rcx # if (n > 0) goto .L2
    jg .L2
    movq    %rdi, %rax # return x
    ret
*/
