
/* Practice Problem 3.30 (solution page 374)
In the C function that follows, we have omitted the body of the switch 
statement.
In the C code, the case labels did not span a contiguous range, 
and some cases had multiple labels. */

void switch2(short x, short *dest) {
    short val = 0;
    switch (x) {

    }
    *dest = val;
}

/*
In compiling the function, gcc generates the assembly code that follows for the initial part of the procedure, with variable x in %rdi:

switch2:
    addq $2, %rdi
    cmpq $8, %rdi
    ja .L2
    jmp *.L4(,%rdi,8)

.L4:
    .quad .L9
    .quad .L5
    .quad .L6
    .quad .L7
    .quad .L2
    .quad .L7
    .quad .L8
    .quad .L2
    .quad .L5

A. What were the values of the case labels in the switch statement?
B. What cases had multiple labels in the C code?
*/

/*
A. The values ranged in [-2 ... 6], because before the add
   operation which was necessary to index the jump table,
   it was possible that the integer was negative.

B. From this information alone, it was basically like this:

   switch (x) {
   case -2:
     goto L9
   case -1:
   case 6:
     goto L5
   case 0:
     goto L6
   case 1:
   case 3:
     goto L7
   // case 2:
   // case 5:
   default:
     goto L2
   }

   I couldn't identify the default case, because guesses
   here aren't really the answer.
*/
