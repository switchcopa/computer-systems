
/*
3.65 ◆
The following code transposes the elements of an M × M array, where M is a constant defined by #define:

void transpose(long A[M][M]) {
    long i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < i; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

When compiled with optimization level -O1, gcc generates the following code for the inner loop of the function: */

.L6:
    movq    (%rdx), %rcx
    movq    (%rax), %rsi
    movq    %rsi, (%rdx)
    movq    %rcx, (%rax)
    addq    $8, %rdx
    addq    $120, %rax
    cmpq    %rdi, %rax
    jne     .L6

/*
We can see that gcc has converted the array indexing to pointer code.

A. Which register holds a pointer to array element A[i][j]?
B. Which register holds a pointer to array element A[j][i]?
C. What is the value of M? 

Answers:

A. %rdx, because we increment per sizeof(long)=8 per iteration.
B. %rax, because we increment per sizeof(long)*M per iteration.
C. Since sizeof(long) * M = 120 => M = 15
*/
