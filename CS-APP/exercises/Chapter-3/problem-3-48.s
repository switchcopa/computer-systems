
/*
Practice Problem 3.48 (solution page 383)
The functions intlen, len, and iptoa provide a very convoluted way to compute
the number of decimal digits required to represent an integer. We will use this as
a way to study some aspects of the gcc stack protector facility.

int len(char *s) {
    return strlen(s);
}

void iptoa(char *s, long *p) {
    long val = *p;
    sprintf(s, "%ld", val);
}

int intlen(long x) {
    long v;
    char buf[12];
    v = x;
    iptoa(buf, &v);
    return len(buf);
}

The following show portions of the code for intlen, compiled both with and
without stack protector:
*/

/* Without protector: 
   long x in %rdi 
*/
    .text
    .globl intlen
intlen:
    subq    $40, %rsp
    movq    %rdi, 24(%rsp)
    leaq    24(%rsp), %rsi
    movq    %rsp, %rdi
    call iptoa

/* With protector 
   long x in %rdi 
*/
    .text
    .globl intlen_prot
intlen_prot:
    subq    $56, %rsp
    movq    %fs:40, %rax
    movq    %rax, 40(%rsp)
    xorl    %eax, %eax
    movq    %rdi, 8(%rsp)
    leaq    8(%rsp), %rsi
    leaq    16(%rsp), %rdi
    call iptoa

/* A. For both versions: What are the positions in the stack frame for buf, v, and
(when present) the canary value?
B. How does the rearranged ordering of the local variables in the protected
code provide greater security against a buffer overrun attack?
*/

/* Answers: 
A. With protector:
   &buf[0] = 16(%rsp) - 28(%rsp)
   &v = 8(%rsp)
   canary value = 40(%rsp)
   Without Protector:
   &buf[0] = 0(%rsp) - 12(%rsp)
   &v = 24(%rsp)
B. I'm not quite sure why, but I think it's because if a
   buffer overrun attack happens, it would be so that the
   attacker modifies the value of the return address,
   the buffer overrun would have to modify the canary value
   with it too, and because it's a randomly generated 64-bit
   value, it is unique in a 2^64 range, therefore it is almost
   impossible to inject the same value.
   Oh wait, it's because if the attacker does a buffer overrun,
   the canary would be corrupted right as when the buffer overflow
   occurs, and so we want to corrupt as much little data as possible.
   If a possible buffer overflow occurs in the case where
   there isn't a canary value, it would silently corrupt the other
   neighboring local variables and invoke undefined behavior within
   the user's program logic.
*/
