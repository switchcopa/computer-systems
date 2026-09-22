
/*
The following program sets the diagonal elements of one of our fixed-sized
arrays to val:
*/

#define N /*_*/

typedef int fix_matrix[N][N];

void fix_set_dag(fix_matrix A, int val) {
    long i;
    for (i = 0; i < N; i++)
        A[i][i] = val;
}

/*
When compiled with optimization level -O1, GCC generates the following
assembly code:

fix_set_dag:
    movl    $0, %eax
.L13:
    movl    %esi, (%rdi, %rax)
    addq    $68, %rax
    cmpq    $1088, %rax
    jne .L13
    rep; ret

Create a C code program fix_set_diag_opt that uses optimizations similar
to those in the assembly code, in the same style as the code in Figure 
3.37(b). Use expressions involving the parameter N rather than integer
constants, so that your code will work correctly if N is redefined.
*/

void fix_set_dag(fix_matrix A, int val) {
    int *Aptr = &A[0][0];
    long i = 0;

    do {
        *Aptr = val;
        Aptr += N + 1;
        i++;
    } while (i < N);
}
