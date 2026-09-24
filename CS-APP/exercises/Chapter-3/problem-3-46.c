
/*
Practice Problem 3.46 (solution page 382)

Figure 3.41 shows a (low-quality) implementation of a function that reads a line
from standard input, copies the string to newly allocated storage, and returns a
pointer to the result.

Consider the following scenario. Procedure get_line is called with the return
address equal to 0x400776 and register %rbx equal to 0x0123456789ABCDEF. You
type in the string

0123456789012345678901234

*/

/* This is very low-quality code.
 * It is intended to show bad programming practices. */

char *get_line() {
    char buf[4];
    char *result;

    gets(buf);
    result = malloc(strlen(buf));
    strcpy(result, buf);
    return result;
}

/*
(b) Disassembly up through call to gets
0000000000400720 <get_line>:

400720: 53              push    %rbx
400721: 48 83 ec 10     sub     $0x10,%rsp

400725: 48 89 e7        mov     %rsp,%rdi
400728: e8 73 ff ff ff  callq   4006a0 <gets>

Modify diagram to show stack contents at this point
Figure 3.41 C and disassembled code for Practice Problem 3.46.

The program terminates with a segmentation fault. You run gdb and determine
that the error occurs during the execution of the ret instruction of get_line.
A. Fill in the diagram that follows, indicating as much as you can about the stack
just after executing the instruction at line 3 in the disassembly. Label the
quantities stored on the stack (e.g., “Return address”) on the right, and their
hexadecimal values (if known) within the box. Each box represents 8 bytes.
Indicate the position of %rsp. Recall that the ASCII codes for characters 0–9
are 0x30–0x39.

B. Modify your diagram to show the effect of the call to gets (line 5).
C. To what address does the program attempt to return?
D. What register(s) have corrupted value(s) when get_line returns?
E. Besides the potential for buffer overflow, what two other things are wrong
with the code for get_line?
*/

/* 
Answers:
A.

[ 00 00 00 00     00   40     00     76   ] <- return address
[ 01 23 45 67     89   AB     CD     EF   ] <- rbx
[ ?? ?? ?? ??     ??   ??     ??     ??   ] <- result
[ ?? ?? ?? ?? buf[3] buf[2] buf[1] buf[0] ] <- rsp
[ 00 00 00 00     00   40     07     2D   ] <- potential return address after the call instruction

B.

[ 00 00 00 00 00 40 00 34 ] <- return address
[ 33 32 31 30 39 38 37 36 ] <- rbx
[ 35 34 33 32 31 30 39 38 ] <- result
[ 37 36 35 34 33 32 31 30 ] <- rsp

The call to gets() corrupts the whole stack up to the
return address, that will soon be popped into %rip
to return back from this get_line function.

C. After incrementing the stack pointer and popping
the saved rbx back, the CPU sees the address 0x400034,
which from there leads to a disaster.

D. %rbx and %rip.
E. I think it's that even though the buffer has already
overflowed, the call to strcpy will attempt to copy
from buf, until it finds a null terminator byte, which
is way until the the 0x00 byte in the return address,
and this call also corrupts the heap address or whatever
memory returned by malloc.
*/
