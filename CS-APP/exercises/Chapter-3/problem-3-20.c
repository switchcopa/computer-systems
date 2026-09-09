
/*
Practice Problem 3.20 (solution page 369)
In the following C function, we have left the definition
of operation OP incomplete:
*/

#define OP /

short arith(short x) {
    return x OP 16;
}

/*
When compiled, gcc generates the following assembly code:
arith:
    leaq 15(%rdi), %rbx
    testq %rdi, %rdi
    cmovns %rdi, %rbx
    sarq $4, %rbx
    ret

A. What operation is OP?
B. Annotate the code to explain how it works.
*/

/*
Let's analyze the assembly code to see what would we get
depending on the input:

leaq 15(%rdi), %rbx

This computes %rbx = x + 15, because lea instructions only
computes offsets.

testq %rdi, %rdi

This evaluates x & x and updates the CPU's %rflags (the condition
codes).

cmovns %rdi, %rbx

This is translated to something like %rbx = (x >= 0) ? x : %rbx
or:

if (x >= 0)
    result = x;
else
    result = x + 15;

sarq $4, %rbx

This computes result >>= 4.
Based on this pattern, we can conclude that it computes
x / 16, truncated towards 0.

A. OP = /
B. lol I just did :3
*/
