
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

/* This example shows how
 * the C standard leaves
 * integer overflow as
 * undefined behavior
 */

__attribute__((noinline))
int does_overflow(int32_t i)
{
    if (i + 1 < i)
    {
        printf("overflow detected.\n");
        return 1;
    }

    return 0;
}

int main(void)
{
    int32_t i = INT32_MAX;
    does_overflow(i);
    return 0;
}

/* There are two main reasons why it never
 * prints "overflow detected":
 *
 * UB Assumptions: The C standard assumes that
 * signed integer overflow is undefined
 * behavior, because older architectures don't
 * universally use the two's complement
 * representation for signed integers. Some use
 * one's complement, or sign magnitude, and so
 * the compilers cannot assume universal signed
 * integer representations.
 * Note: while C23 abandoned support for one's
 * complement or sign magnitude, and now only
 * supports two's complement, but signed integer
 * overflow is still considered UB.
 *
 * Optimization: Compiler optimizers need to
 * maximize raw execution speeds, along with
 * the no-UB assumptions, i + 1 < i is not
 * logically possible, consequently, it does
 * dead-code elimination and removes that
 * if-branch
 *
 * Note on the __attribute__((noinline)):
 * we used this GCC extension to force the
 * compiler to simulate real world heavy functions
 * that cannot be inlined, because this is a small
 * program and inputs are known at compile time.
 */
