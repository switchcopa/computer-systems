
/*
Problem: Translate the following C function to assembly:

double funct(double a, float x, double b, int i) {
    return a*x - b/i;
}
*/
    .text
    .globl funct
funct:
    vunpcklps %xmm1, %xmm1, %xmm1
    vcvtps2pd %xmm1, %xmm1
    vmulsd  %xmm1, %xmm0, %xmm0
    vcvtsi2sd %edi, %xmm1, %xmm1
    vdivsd  %xmm1, %xmm2, %xmm2
    vsubsd  %xmm2, %xmm0, %xmm0
    ret
