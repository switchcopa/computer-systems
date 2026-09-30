
/* w = xmm0, x = edi, y = xmm1, z = rsi */
    .text
    .globl funct2
funct2:
    vcvtsi2ss %edi, %xmm2, %xmm2
    vmulss %xmm1, %xmm2, %xmm1
    vunpcklps %xmm1, %xmm1, %xmm1
    vcvtps2pd %xmm1, %xmm2
    vcvtsi2sdq %rsi, %xmm1, %xmm1
    vdivsd %xmm1, %xmm0, %xmm0
    vsubsd %xmm0, %xmm2, %xmm0
    ret
