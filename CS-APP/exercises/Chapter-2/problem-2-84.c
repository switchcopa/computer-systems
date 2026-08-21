/*
2.84 ◆
Fill in the return value for the following procedure, which tests whether its first
argument is less than or equal to its second. Assume the function f2u returns an
unsigned 32-bit number having the same bit representation as its floating-point
argument. You can assume that neither argument is NaN. The two flavors of zero,
+0 and −0, are considered equal.

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return // your expression here ;
}
*/

unsigned f2u(float x) {
    union pun {
        unsigned u;
        float f;
    } t;

    t.f = x;
    return t.u;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    int mask_x = (int)ux >> 31;
    int mask_y = (int)uy >> 31;

    int sx = (ux ^ (mask_x & 0x7FFFFFFF)) + (mask_x & 1);
    int sy = (uy ^ (mask_y & 0x7FFFFFFF)) + (mask_y & 1);

    int both_zero = !((ux | uy) & 0x7FFFFFFF);
    return both-zero | (sx <= sy);
}
