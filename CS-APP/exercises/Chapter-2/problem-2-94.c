
/* 2.94 ◆◆◆
Following the bit-level floating-point coding rules, implement the function with
the following prototype:
Compute 2*f. If f is NaN, then return f. */

/*
float_bits float_twice(float_bits f);

For floating-point number f , this function computes 2.0 . f . If f is NaN, your
function should simply return f .
Test your function by evaluating it for all 232 values of argument f and com-
paring the result to what would be obtained using your machine’s floating-point
operations.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

typedef unsigned float_bits;

int is_special(float_bits f)
{
    uint8_t exp = (f >> 23) & 0xFF;
    return !((uint8_t)(~exp) & 0xFF);
}

float_bits float_twice(float_bits f)
{
    if (is_special(f))
        return f;

    uint8_t sign = f >> 31;
    uint8_t exp = (f >> 23) & 0xFFu;
    unsigned frac = f & 0x7FFFFF;

   switch (exp) {
   case UINT8_MAX - 1:
        exp += 1;
        frac = 0;
        break;
    case 0:
        frac <<= 1;
        break;
    default:
        exp += 1;
        break;
    }

    return (sign << 31) | (exp << 23) | frac;
}

float_bits float_twice_expected(float_bits f)
{
    if (is_special(f))
        return f;

    float x;
    float_bits ret;

    memcpy(&x, &f, sizeof(float));
    x *= 2.0f;
    memcpy(&ret, &x, sizeof(float));
    return ret;
}

int main(void)
{
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

    const char *err_msg = 
            RED
            "[FAILED]: Test Suite Failed for Value 0x%X\n"
            "Value Produced: 0x%X\n"
            "Value Expected: 0x%X\n" RESET ;

    float_bits (*test_function)(float_bits);
    float_bits (*expected)(float_bits);

    test_function = float_twice;
    expected = float_twice_expected;

    for (float_bits b = 0U; b < UINT_MAX; b++)
        if (test_function(b) != expected(b)) {
            printf(err_msg, b, test_function(b), expected(b));
            return 1;
        }

    printf(GREEN "[SUCCESS]: ALL ASSERTIONS PASSED!\n" RESET);
    return 0;
}
