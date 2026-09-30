
/*
Practice Problem 3.54 (solution page 385)
Function funct2 has the following prototype:

double funct2(double w, int x, float y, long z);

GCC generates the following code for the function:
**Look at problem-3-54.s**
*/

/* w = xmm0, x = edi, y = xmm1, z = rsi */

double funct2(double w, int x, float y, long z) {
    float t0 = (float)x;    // vcvtsi2ss %edi, %xmm2, %xmm2
    y = y * t0;             // vmulss %xmm1, %xmm2, %xmm1
    double t1 = (double)y;  // vunpcklps %xmm1, %xmm1, %xmm1
                            // vcvtps2pd %xmm1, %xmm2
    double t2 = (double)z;  // vcvtsi2sdq %rsi, %xmm1, %xmm1
    w = w / t2;             // vdivsd %xmm1, %xmm0, %xmm0
    w = t1 - w;             // vsubsd %xmm0, %xmm2, %xmm0
    return w;               // ret
}

double funct2_simple(double w, int x, float y, long z) {
    return (x * y) - (w / z);
}
