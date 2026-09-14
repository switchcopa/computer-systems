/*
Practice Problem 3.39 (solution page 378)
Use Equation 3.1 to explain how the computations of the initial values for Aptr,
Bptr, and Bend in the C code of Figure 3.37(b) (lines 3–5) correctly describe their
computations in the assembly code generated for fix_prod_ele (lines 3–5).

The C code goes like this:
*/

#define N 16
typedef int fix_matrix[N][N];

int fix_prod_ele_opt(fix_matrix A, fix_matrix B, long i, long k) {
    int *Aptr = &A[i][0];
    int *Bptr = &B[0][k];
    int *Bend = &B[N][k];
    int result = 0;
    do {
        result += *Aptr * *Bptr;
        Aptr++;
        Bptr += N;
    } while (Bptr < Bend);
    return result;
}

/*
And the assembly code is like this:

fix_prod_ele_opt:
    salq    $6, %rdx
    addq    %rdx, %rdi
    leaq    (%rsi, %rcx, 4), %rcx
    leaq    1024(%rcx), %rsi
    xorl    %eax, %eax
.L7:
    movl    (%rdi), %edx
    imull   (%rcx), %edx
    addl    %edx, %eax
    addq    $4, %rdi
    addq    $64, %rcx
    cmpq    %rsi, %rcx
    jne .L7
    ret

Equation 3.1 says:
&D[i][j] = base + L(C*i + j)
The addresses computed in Line 3, 4 and 5 used this exact
formula. They took the base address &A[0][0] and &B[0][0],
because that's how they were passed under the hood, then
they increment based on the rows and columns.
*/
