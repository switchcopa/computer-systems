
/*
Practice Problem 3.16 (solution page 367)
When given the C code

void cond(short a, short *p)
{
    if (a && *p < a)
        *p = a;
}

GCC generates the following assembly code:

    .global cond
cond:
    testw   %di, %di
    je .L0
    cmpw    (%rsi), %di
    jle .L0
    movw    %di, (%rsi)
.L0:
    ret

A. Write a goto version in C that performs the same computation and mimics
the control flow of the assembly code, in the style shown in Figure 3.16(b).
You might find it helpful to first annotate the assembly code as we have done
in our examples.
B. Explain why the assembly code contains two conditional branches, even
though the C code has only one if statement.
*/

void cond(short a, short *p) {
    if (a == 0)
        goto L0;
    if (*p >= a)
        goto L0;
    *p = a;
L0:
    return;
}

/*
B. It's because of short-circuit evaluation, the machine
has to exit evaluation of the expressions early if a condition
is not meant.

You may ask:
How can the machine replicate the behavior of the high-level
C '&&' logical operator?
We have to apply De Morgan's Laws to the logical expression
to achieve equivalence:

    ~(A & B) <=> ~A | ~B

This is how it evaluates the expression, so if A is false,
it won't check B, because problems can occur, for example:

void dereference(int *p) {
    if (p != NULL && *p == 5)
        *p = 10;
}

The assembly translation of this is:
    // p in %rdi

dereference:
    testq %rdi, %rdi
    je .L0
    cmpl $5, (%rdi)
    jne .L0
    movl $10, (%rdi)
.L0:
    ret

If it executed all the branches at once, the dereference
of the pointer when it is NULL would be UB and segfault
on a modern machine.
*/
