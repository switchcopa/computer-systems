
/* Practice Problem 4.3 (solution page 518)
One common pattern in machine-level programs is to add a constant value to a
register. With the Y86-64 instructions presented thus far, this requires first using an
irmovq instruction to set a register to the constant, and then an addq instruction to
add this value to the destination register. Suppose we want to add a new instruction
iaddq with the following format: 

Byte         0    1      2               10
iaddq V, rB  [C 0 | F rB |       V       ]

This instruction adds the constant value V to register rB.
Rewrite the Y86-64 sum function of Figure 4.6 to make use of the iaddq
instruction. In the original version, we dedicated registers %r8 and %r9 to hold
constant values. Now, we can avoid using those registers altogether.
*/

sum:
    xorq    %rax, %rax
    andq    %rsi, %rsi
    jmp test
loop:
    mrmovq  (%rdi), %rdx
    addq    %rdx, %rax
    iaddq   $8, %rdi
    iaddq   $-1, %rsi
test:
    jne loop
    ret
