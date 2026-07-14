

/*
Practice Problem 2.30 (solution page 189)
Write a function with the following prototype:

// determine whether arguments can be added without overflow
int tadd_ok(int x, int y);

This function should return 1 if arguments x and y can be added without
causing overflow.
*/

/*
Solution: what we can do is basically cast the arguments to be
unsigned integers, add the results together, convert back to signed,
and then use the XOR operator on the operands like so: */

int tadd_ok(int x, int y)
{
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    unsigned usum = ux + uy;

    signed int sum = (int)usum;

    if ((x ^ y) >= 0 && (sum ^ x) < 0)
        return 0;
    return 1;
}

/*
The expression (x ^ y) >= 0 evaluates to 1 if both x and y have the
same sign. To visualize this, imagine their sign bit to be either
both 0 or both 1, so the result x ^ y has its sign bit off, and that
determines its positivity.
Same thing for (sum ^ x) < 0, except it determines whether sum and x
have different signs.

Another safer alternative is to use the macros defined in <limits.h>
that provide the ranges for each data type, which is very ISO C
standard compliant:
*/

#include <limits.h>

int tadd_ok2(int x, int y)
{
    if (y > 0)
        return x <= INT_MAX - y;
    else
        return x >= INT_MIN - y;
}
