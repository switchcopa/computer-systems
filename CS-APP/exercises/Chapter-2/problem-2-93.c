
/* 2.93 ◆◆
Following the bit-level floating-point coding rules, implement the function with
the following prototype:
Compute |f|.
If f is NaN, then return f. */

/*
float_bits float_absval(float_bits f);
For floating-point number f , this function computes |f |. If f is NaN, your
function should simply return f .
Test your function by evaluating it for all 232 values of argument f and com-
paring the result to what would be obtained using your machine’s floating-point
operations. */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h> /* for fabs(double) */

typedef unsigned float_bits;

int is_nan(float_bits f)
{
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    return !(~exp) && frac;
}

float_bits float_absval(float_bits f)
{
    if (is_nan(f))
        return f;

    f &= ~(1U << 31);
    return f;
}

float_bits float_absval_expected(float_bits f)
{
    float x;
    float_bits ret;

    memcpy(&x, &f, sizeof(float));
    x = fabs(x);

    memcpy(&ret, &x, sizeof(float));
    return ret;
}

void main(void)
{
    float_bits (*test_function)(float_bits);
    float_bits (*expected)(float_bits);

    test_function = float_absval;
    expected = float_absval_expected;

    for (float_bits b = 0U; b < UINT_MAX; b++)
        if (test_function(b) != expected(b))
            printf("[FAILED]: Test Suite Failed for Value %X :(\n", b);

    printf("[SUCCESS]: ALL ASSERTIONS PASSED!\n");
}
