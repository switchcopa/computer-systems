
/*
2.96 ◆◆◆◆
Following the bit-level floating-point coding rules, implement the function with
the following prototype: 
*/
/*
* Compute (int) f.
* If conversion causes overflow or f is NaN, return 0x80000000
*/
/* int float_f2i(float_bits f);
For floating-point number f , this function computes (int) f . Your function
should round toward zero. If f cannot be represented as an integer (e.g., it is out
of range, or it is NaN), then the function should return 0x80000000.
Test your function by evaluating it for all 232 values of argument f and com-
paring the result to what would be obtained using your machine’s floating-point
operations. */

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

typedef uint32_t float_bits;

int32_t float_f2i(float_bits f)
{
    uint8_t sign = f >> 31;
    uint8_t exp  = (f >> 23) & 0xFF;
    uint32_t frac = f & 0x7FFFFF;

    int16_t E = (int16_t)exp - 0x7F;

    if (E < 0) return 0;
    if (E >= 31) return 0x80000000;

    int32_t M = frac | 0x800000;
    int32_t result = (E >= 23) ? (M << (E - 23)) :
                                 (M >> (23 - E));

    return sign ? -result : result;
}

int32_t float_f2i_expected(float_bits f)
{
    uint8_t exp  = (f >> 23) & 0xFF;
    int16_t E = (int16_t)exp - 0x7F;

    if (E < 0) return 0;
    if (E >= 31) return 0x80000000;

    union pun {
        int32_t i;
        float f;
    } t;

    t.i = (int32_t)f;

    return (int32_t)t.f;
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

    int32_t (*test_function)(float_bits);
    int32_t (*expected)(float_bits);

    test_function = float_f2i;
    expected = float_f2i_expected;

    for (float_bits b = 0U; b < UINT32_MAX; b++)
        if (test_function(b) != expected(b)) {
            printf(err_msg, b, test_function(b), expected(b));
            return 1;
        }

    printf(GREEN "[SUCCESS]: ALL ASSERTIONS PASSED! :DDD\n" RESET);
    return 0;
}
