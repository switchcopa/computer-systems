
/*
Practice Problem 3.57 (solution page 386)
Function funct3 has the following prototype:

double funct3(int *ap, double b, long c, float *dp);

For this function, gcc generates the following code:

funct3:
    vmovss (%rdx), %xmm1
    vcvtsi2sd (%rdi), %xmm2, %xmm2
    vucomisd %xmm2, %xmm0
    jbe .L8
    vcvtsi2ssq %rsi, %xmm0, %xmm0
    vmulss %xmm1, %xmm0, %xmm1
    vunpcklps %xmm1, %xmm1, %xmm1
    vcvtps2pd %xmm1, %xmm0
    ret
.L8:
    vaddss %xmm1, %xmm1, %xmm1
    vcvtsi2ssq %rsi, %xmm0, %xmm0
    vaddss %xmm1, %xmm0, %xmm0
    vunpcklps %xmm0, %xmm0, %xmm0
    vcvtps2pd %xmm0, %xmm0
    ret
*/

double funct3(int *ap, double b, long c, float *dp)
{
    float d = *dp;
    int a = *ap;
    if ((double)a >= b)
        return (double)((float)c + 2.0 * d);
    else
        return (double)(d * (float)c);
}
