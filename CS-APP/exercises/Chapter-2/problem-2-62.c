
/*
2.62 ◆◆◆
Write a function int_shifts_are_arithmetic() that yields 1 when run on a
machine that uses arithmetic right shifts for data type int and yields 0 otherwise.
Your code should work on a machine with any word size. Test your code on several
machines.
*/

/* let's inspect the assembly and see the instruction that is generated 
 * for an arithmetic right shift */

#include <stdio.h>

int int_shifts_are_arithmetic()
{
    int x = -1;
    return !((x >> 1) ^ -1);
}

void main(void)
{
    printf("%d\n", int_shifts_are_arithmetic());
}
