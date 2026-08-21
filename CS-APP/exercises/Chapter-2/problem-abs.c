
/*
Custom Problem (Given by Google Gemini AI)

Write code for a function with the following prototype:
*/

/* Absolute value of x */

/*
int abs(int x);

Your function should compute and return the absolute value of the signed
integer type x. Be careful about edge cases like TMIN or TMAX.
Your function should follow the bit-level integer coding rules (page 164).
*/

int abs(int x) {
    int shift = (sizeof(int) << 3) - 1;
    int neg = x >> shift;

    return (x ^ neg) - neg;
}

#include <stdio.h>
#include <limits.h>
#include <assert.h>

void main(void) {
    assert(abs(0) == 0);
    assert(abs(1) == 1);
    assert(abs(-1) == 1);
    assert(abs(12345) == 12345);
    assert(abs(-12345) == 12345);
    assert(abs(INT_MAX) == INT_MAX);
    assert(abs(INT_MIN) == INT_MIN);

    printf("All test cases passed successfully!\n");
}
