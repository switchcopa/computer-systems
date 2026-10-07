
/*
3.64 ◆◆◆
Consider the following source code, where R, S, and T are constants declared with
#define:
In compiling this program, gcc generates the following assembly code:


store_ele:
    leaq    (%rsi,%rsi,2), %rax
    leaq    (%rsi,%rax,4), %rax
    movq    %rdi, %rsi
    salq    $6, %rsi
    addq    %rsi, %rdi
    addq    %rax, %rdi
    addq    %rdi, %rdx
    movq    A(,%rdx,8), %rax     
    movq    %rax, (%rcx)
    movl    $3640, %eax
    ret

A. Extend Equation 3.1 from two dimensions to three to provide a formula for
the location of array element A[i][j][k].

B. Use your reverse engineering skills to determine the values of R, S, and T
based on the assembly code.


Answers:
    A. We see that the index is calculated with
        index = i * (S * T) + j * T + k
    B. By my careful reading of this problem, I
       see that:

        rdx = i * 65 + j * 13 + k
        So T = 13, because to skip by one j, you
        need to skip by an entire row j.
        S is dependent on the ratio between the i
        coefficient and the j coefficient:
        S = S * T / T = 65/13 = 5

       Next, given the size of the array:
{
// ...
    return sizeof(A); // movl    $3640, %eax
}
       So:
    sizeof(A) = R * S * T * sizeof(long) = 3640
    => R = sizeof(A)/(S*T*sizeof(long)) = 3640/(5*13*8)
    => R = 7
*/

#define R  7
#define S  5
#define T 13

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}
