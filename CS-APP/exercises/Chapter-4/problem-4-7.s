
/* x86-64 Program to test the behavior of
   the pushq instruction, when the
   instruction is pushq %rsp.
   The question is: does the stack pointer
   value get decremented first, or does the
   processor write to the stack then
   decrement the stack pointer stored in the
   %rsp register? We test this with the
   following program */

    .text
    .globl  pushtest
pushtest:
    movq    %rsp, %rax
    pushq   %rsp
    popq    %rdx
    subq    %rdx, %rax
    ret

    .globl  main
main:
    call    pushtest
    ret

/* We run the program using GDB, we run
   the commands x/gx $sp, before and after
   the stack push:

pushtest () at problem-4-7.s:15
15          movq    %rsp, %rax
(gdb) p/x $sp
$1 = 0x7fffffffe660
(gdb) n
16          pushq   %rsp
(gdb)
pushtest () at problem-4-7.s:17
17          popq    %rdx
(gdb) x/gx $sp
0x7fffffffe658: 0x00007fffffffe660 */

/* We see that right after the pushq
   instruction, the value of %rsp was
   written as it was before decrementing,
   and the value returned by %rax was 0. */
/* In conclusion: The value of %rsp is
   written before it is decremented */
