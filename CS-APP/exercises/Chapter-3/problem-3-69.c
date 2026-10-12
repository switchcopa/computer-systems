
/*
3.69 ◆◆◆
You are charged with maintaining a large C program, and you come across the
following code: */

#define CNT

typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

void test(long i, b_struct *bp)
{
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}

/*
The declarations of the compile-time constant CNT and the structure a_struct
are in a file for which you do not have the necessary access privilege. Fortunately,
you have a copy of the .o version of code, which you are able to disassemble with
the objdump program, yielding the following disassembly:

void test(long i, b_struct *bp)

0000000000000000 <test>:
0: 8b 8e 20 01 00 00    mov 288(%rsi),%ecx
6: 03 0e                add (%rsi),%ecx
8: 48 8d 04 bf          lea (%rdi,%rdi,4),%rax
c: 48 8d 04 c6          lea (%rsi,%rax,8),%rax ; rax = bp + i*40
10: 48 8b 50 08         mov 8(%rax),%rdx ; acquire int ap->idx
14: 48 63 c9            movslq %ecx,%rcx ; sign extend n to quadword (long x[])
17: 48 89 4c d0 10      mov %rcx, 16(%rax,%rdx,8)
1c: c3                  retq

Using your reverse engineering skills, deduce the following:
A. The value of CNT.
B. A complete declaration of structure a_struct. Assume that the only fields
in this structure are idx and x, and that both of these contain signed values.
*/

/*
Solution:
A. Size of a_struct: The instruction lea (%rsi,%rax,8),%rax,
where rax = i * 5 means rax = i * 40.
This tells us immediately that sizeof(a_struct) = 40 bytes.

Offset of b_struct->a: b_struct starts with int first;
We can see from the movslq instruction that a_struct
requires 8-byte alignment, because it contains long
types. Hence, array a starts at offset 8.

CNT: bp->last is accessed at offset 288:

offsetof(last) - offsetof(a) = 280 bytes.

Hence:
CNT = 280/40 = 7.

B.

typedef struct {
    long idx;
    long x[4];
} a_struct;

*/
