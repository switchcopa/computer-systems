
/*
3.62 ◆◆
The code that follows shows an example of branching 
on an enumerated type value in a switch statement. 
Recall that enumerated types in C are simply a way
to introduce a set of names having associated integer values.
By default, the values assigned to the names count from 
zero upward. 
In our code, the actions associated with the different case 
labels have been omitted. */

typedef enum { MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
    long result = 0;

    switch (action) {
    case MODE_A:
        result = *p2;
        *p2 = *p1;
        return result;
    case MODE_B:
        result = *p1;
        result += *p2;
        *p1 = result;
        return result;
    case MODE_C:
        *p1 = 59;
        result = *p2;
        return result;
    case MODE_D:
        *p1 = *p2;
    case MODE_E:
        return 27;
    default:
        return 12;
    }
}

/* The part of the generated assembly code implementing the different actions is
shown in Figure 3.52. The annotations indicate the argument locations, the register
values, and the case labels for the different jump destinations.
Fill in the missing parts of the C code. It contained one case that fell through
to another—try to reconstruct this. 

Figure 3.52: Assembly code for Problem 3.62. This code implements the different
branches of a switch statement.

.L8: MODE_E
    movl $27, %eax
    ret
.L3: MODE_A
    movq (%rsi), %rax
    movq (%rdi), %rdx
    movq %rdx, (%rsi)
    ret
.L5: MODE_B
    movq (%rdi), %rax
    addq (%rsi), %rax
    movq %rax, (%rdi)
    ret
.L6: MODE_C
    movq $59, (%rdi)
    movq (%rsi), %rax
    ret
.L7: MODE_D
    movq (%rsi), %rax
    movq %rax, (%rdi)
    movl $27, %eax
    ret
.L9: default
    movl $12, %eax
    ret
*/
