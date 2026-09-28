
/*
Practice Problem 3.50 (solution page 383)

For the following C code, the expressions 
val1–val4 all map to the program values i, f, d, and l:

double fcvt2(int *ip, float *fp, double *dp, long l) {
    int i = *ip;
    float f = *fp;
    double d = *dp;

    *ip = (int)VAL1;
    *fp = (float)VAL2;
    *dp = (double)VAL3;

    return (double)VAL4;
}

Determine the mapping, based on the following x86-64 code for the function:

Here: VAL1 = d
      VAL2 = i
      VAL3 = l
      VAL4 = f
*/
    .text
    .globl fcvt2
fcvt2:
    movl    (%rdi), %eax # i = *ip
    vmovss  (%rsi), %xmm0 # f = *fp
    vcvttsd2si  (%rdx), %r8d # t0 = (int)*dp
    movl    %r8d, (%rdi) # *ip = t0
    vcvtsi2ss   %eax, %xmm1, %xmm1 # t1 = (float)i
    vmovss  %xmm1, (%rsi) # *fp = t1
    vcvtsi2sdq  %rcx, %xmm1, %xmm1 # t2 = (double)l
    vmovsd  %xmm1, (%rdx) # *dp = t2
    vunpcklps   %xmm0, %xmm0, %xmm0 # t3 = (double)f ??
    vcvtps2pd   %xmm0, %xmm0 # return = (double)t3
    ret
