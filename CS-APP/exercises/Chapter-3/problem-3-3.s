
/*
Each of the following lines of code generates an error message when we invoke
the assembler. Explain what is wrong with each line.
*/

    movb $0xF, (%ebx)
    movl %rax, (%rsp)
    movw (%rax),4(%rsp)
    movb %al,%sl
    movq %rax,$0x123
    movl %eax,%rdx
    movb %si, 8(%rbp)

/*
1. We're attempting to dereference a 32-bit address.
2. The suffix 'l' does not match either operand.
3. We can't perform any instruction whose operands
   are both memory references.
4. Suffix 'b' does not match either 16-bit word operands.
5. Attempt to move a register to immediate value.
6. The assembler requires both operands to match
   the size indicated by the suffix (l, 32-bit)
7. Size mismatch between suffix and source register, which
   is 16-bit wide.
*/
