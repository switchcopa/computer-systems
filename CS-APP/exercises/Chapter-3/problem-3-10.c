
/*
Practice Problem 3.10 (solution page 365)
Consider the following code, in which we have omitted the expression being
computed:

short arith3(short x, short y, short z)
{
    short p1 = __ ;
    short p2 = __ ;
    short p3 = __ ;
    short p4 = __ ;
    return p4;
}

The portion of the generated assembly code implementing these expressions
is as follows:

short arith3(short x, short y, short z)
x in %rdi, y in %rsi, z in %rdx

arith3:
    orq  %rsi, %rdx
    sarq $9, %rdx
    notq %rdx
    movq %rdx, %rax
    subq %rsi, %rax
    ret

Based on this assembly code, fill in the missing portions of the C code.
*/


short arith3(short x, short y, short z)
{
    short p1 = y | z;
    short p2 = p1 >> 9;
    short p3 = ~p2;
    short p4 = p3 - y;
    return p4;
}
