
/*
Practice Problem 3.11 (solution page 365)
It is common to find assembly-code lines of the form

    xorq %rcx,%rcx

in code that was generated from C where no exclusive-or operations were
present.

A. Explain the effect of this particular exclusive-or instruction and what useful
operation it implements.

B. What would be the more straightforward way to express this operation in
assembly code?

C. Compare the number of bytes to encode any two of these three different
implementations of the same operation.
*/

/* 
A. This effect of the XOR instruction is zero-ing out a register,
and it's useful for quickly setting a register to 0. Though it may
not be any faster on modern processors, optimizers often prefer this
because it saves the amount of bytes to encode an instruction that
zeroes out a register.

B. A more straightforward way to express this operation in assembly
is to do a movement instruction like:

    movq    $0, %rax
instead. It is more understandable this way.

C. Let's do this ourselves and see the difference.
First of all, create a file called xorq.c and compile with GCC:

long xorq(void) {
    return 0;
}

```
gcc -std=c11 -O0 -fno-stack-protector -fomit-frame-pointer xorq.c -c xorq.o
```

and then invoke the disassembler objdump:

```
objdump -d xorq.o
```

We see the following output:


xorq.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <xorq>:
   0:	b8 00 00 00 00       	mov    $0x0,%eax
   5:	c3                   	ret

We see that the instruction to move 0 to %eax takes 5 bytes.
Somehow it didn't generate code to move for the full 64-bit %rax
register, that would actually take 7 bytes to encode.

Now let's compile it with optimization flags enabled, preferably
with -O2

```
gcc -std=c11 -O2 -fno-stack-protector -fomit-frame-pointer xorq.c -c xorq.o
objdump -d xorq.o
```

We get the following output:

xorq.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <xorq>:
   0:	31 c0                	xor    %eax,%eax
   2:	c3                   	ret

The compiler optimizer emitted this instruction instead.
We see clearly that the instruction takes 2 bytes instead of 5.
This is more efficient, and also smart, because these certain
arithmetic instruction done on the 32-bit lower half of the 
general purpose registers automatically zero out the upper
32-bit half.
*/
