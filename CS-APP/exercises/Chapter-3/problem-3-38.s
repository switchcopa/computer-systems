
/*
Practice Problem 3.38 (solution page 377)
Consider the following source code, where M and N are constants declared with
#define:

long P[M][N];
long Q[N][M];

long sum_element(long i, long j) {
    return P[i][j] + Q[j][i];
}

In compiling this program, gcc generates the following assembly code:
*/

    .text
    .globl sum_element
sum_element:
    leaq 0(,%rdi,8), %rdx
    subq %rdi, %rdx
    addq %rsi, %rdx
    leaq (%rsi,%rsi,4), %rax
    addq %rax, %rdi
    movq Q(,%rdi,8), %rax
    addq P(,%rdx,8), %rax
    ret

/*
Use your reverse engineering skills to determine the values of M and N based
on this assembly code. 

rax = Q[i + j * 5] + P[j + i * 7]

(char *)&Q[0][0] + 5 * j + i
(char *)&P[0][0] + 7 * i + j

We see that for each row that Q skips, its size is 5.
We see that for each row that P skips, its size is 7.
And so:

#define M 7
#define N 5
*/
