
/*
Practice Problem 3.42 (solution page 379)
The following code shows the declaration of a structure of type ACE and the
prototype for a function test: */

struct ACE {
    short v;
    struct ACE *p;
};

short test(struct ACE *ptr) {
    short ax = 1;
    while (ptr != (void*)0) {
        ax *= ptr->v;
        ptr = ptr->p;
    }

    return ax;
}

/*
When the code for test is compiled, GCC generates the following assembly
code:

test:
    movl    $1, %eax
    jmp .L2
.L3:
    imulq   (%rdi), %rax
    movq    2(%rdi), %rdi
.L2:
    testq   %rdi, %rdi
    jne .L3
    rep; ret

A. Use your reverse engineering skills to write C code for test.
B. Describe the data structure that this structure implements 
and the operation performed by test.

B. The data structure used is a linked list, the operation performed
is to get all the data from the linekd list and multiply them together.
Basically the product of all the nodes.

Side Note: I can discuss that this assembly code is handwritten,
because it is very buggy. From what I've seen in the CS:APP book,
it uses the data type short, and then uses the 64-bit version of
registers for their assembly equivalent. This might be just for
simplification, but let's take a look at this snippet:

    imulq   (%rdi), %rax
    movq    2(%rdi), %rdi

imulq fetches the field v from (%rdi) using the suffix 'q',
meaning take the quad-word stored at %rdi, and multiply it
with %rax. Then the next line fetches the quad-word at 2(%rdi),
which already aliases with the other member. This introduces
alignemnt issues and logic issues too. Fetching (%rdi) takes
whatever the lower 6 bytes p stores from its address.
*/
