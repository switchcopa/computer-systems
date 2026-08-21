
/* 2.95 ◆◆◆
Following the bit-level floating-point coding rules, implement the function with
the following prototype: */
/* Compute 0.5*f.
If f is NaN, then return f. */

/*
float_bits float_half(float_bits f);

For floating-point number f , this function computes 0.5 . f . If f is NaN, your
function should simply return f .
Test your function by evaluating it for all 232 values of argument f and com-
paring the result to what would be obtained using your machine’s floating-point
operations. */

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

typedef uint32_t float_bits;

float_bits float_half(float_bits f)
{
    uint8_t  sign = f >> 31;
    uint8_t  exp  = (f >> 23) & 0xFFu;
    uint32_t frac = f & (uint32_t)0x7FFFFF;

    if (exp == 0xFFu)
        return f;

    uint8_t transition = (exp == 1u);
    uint8_t denorm = (exp <= 1u);

    frac |= ((uint32_t)transition << 23);

    uint8_t round = (frac & 1) & (frac >> 1) & denorm;

    frac >>= denorm;
    frac += round;
    exp -= (exp > 0u);

    uint8_t overflow = (frac >> 23) & 1u;
    exp += overflow & denorm;

    return ((uint32_t)sign << 31) |
            ((uint32_t)exp << 23) | 
            (frac & (uint32_t)0x7FFFFF);
}

float_bits float_half_expected(float_bits f)
{
    uint8_t exp = (f >> 23) & 0xFFu;
    if (exp == 0xFFu)
        return f;

    union pun {
        float_bits u;
        float f;
    } t;

    t.u = f;
    t.f *= 0.5f;

    return t.u;
}

int main(void)
{
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

    const char *err_msg = 
        RED "[FAILED]: Test Suite Failed for Value 0x%X\n"
            "Value Produced: 0x%X\n"
            "Value Expected: 0x%X\n" RESET ;

    float_bits (*test_function)(float_bits);
    float_bits (*expected)(float_bits);

    test_function = float_half;
    expected = float_half_expected;

    for (float_bits b = 0U; b < UINT32_MAX; b++)
        if (test_function(b) != expected(b)) {
            printf(err_msg, b, test_function(b), expected(b));
            return 1;
        }

    printf(GREEN "[SUCCESS]: ALL ASSERTIONS PASSED! :DDD\n" RESET);
    return 0;
}
