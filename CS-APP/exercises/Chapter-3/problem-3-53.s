
/*
Practice Problem 3.53 (solution page 384)
For the following C function, the types of the four arguments are defined by
typedef:

double funct1(arg1_t p, arg2_t q, arg3_t r, arg4_t s)
{
    return p/(q+r) - s;
}

typedef int arg1_t;
typedef float arg2_t;
typedef long arg3_t;
typedef double arg4_t;
*/

# rsi = long r
# xmm0 = float q
# edi = int p
# xmm1 = double s

    .text
    .globl funct1
funct1:
    vcvtsi2ssq  %rsi, %xmm2, %xmm2
    vaddss  %xmm0, %xmm2, %xmm0
    vcvtsi2ss   %edi, %xmm2, %xmm2
    vdivss  %xmm0, %xmm2, %xmm0
    vunpcklps   %xmm0, %xmm0, %xmm0
    vcvtps2pd   %xmm0, %xmm0
    vsubsd  %xmm1, %xmm0, %xmm0
    ret
