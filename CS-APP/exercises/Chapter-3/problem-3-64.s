
/*
Practice Problem 3.64

Consider the following C source code, where `R`, `S`, and `T` are constants declared with `#define`:

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
} 

In compiling this program, gcc generates the following x86-64 assembly code:
*/

; long store_ele(long i, long j, long k, long *dest)
; i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:

    ; rax = 13*j
    leaq    (%rsi,%rsi,2), %rax
    leaq    (%rsi,%rax,4), %rax

    ; rdx = i*65 + 13*j + k

    movq    %rdi, %rsi
    salq    $6, %rsi
    addq    %rsi, %rdi
    addq    %rax, %rdi
    addq    %rdi, %rdx

    ; t = *(A + rdx * 8)
    ; *dest = t
    ; return 3640

    movq    A(,%rdx,8), %rax
    movq    %rax, (%rcx)
    movl    $3640, %eax
    ret

/* Questions

A. Extend Equation 3.1 from two dimensions to three to provide a formula for the location of array element A[i][j][k].   

B. Use your reverse engineering skills to determine the values of R, S, and T based on the assembly code.

Answers

A. The equation is 
Address of A[i][j][k] = base + L×((i×R + j)×S + k),
where L = sizeof(each element), R = total number of layers,
      S = total numbers of rows in the layer
It's because we basically skip i*R layers, and j*S rows, and k columns.

B. We have &A[i][j][k] = &A[0][0][0] + L*((i*R + j)*S + k) = 3640
Assume A = NULL, here L = 8:

&A[i][j][k] = (i*R + j)*S + k = i*65 + 13*j + k = 455
k doesn't contribute so:

i*65 + 13*j = (i*R + j)*S = i*R*S + j*S = 455 - k
We can see that:

 { R*C = 65     hence
{                   => R = 5 and S = 13
 { C = 13

Also:
sizeof(A) = sizeof(long) * (R * S * T) = 8 * 5 * 13 * T = 3640
Hence T = 7
*/
