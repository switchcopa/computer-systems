
/*
Custom Google Gemini AI problem

Write code for a function with the following prototype:
C

* Determine whether x < y *
int is_less(int x, int y);
*/

/*
Your function should return 1 if x<y, and 0 otherwise. Be careful about edge cases like potential overflow when x and y have opposite signs (e.g., involving TMin or TMax).

Your function should follow the bit-level integer coding rules (page 164).
*/

#include <stdio.h>
#include <limits.h>
#include <assert.h>

int is_less(int x, int y)
{
    int shift = (sizeof(int) << 3) - 1;

    int sx = (x >> shift) & 1;
    int sy = (y >> shift) & 1;

    int diff_sign = sx ^ sy;

    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    int neg = (int)((ux - uy) >> shift) & 1;

    return (diff_sign & sx) | (~diff_sign & neg);
}

void main(void)
{
    assert(is_less(3, 5) == 1);
    assert(is_less(5, 3) == 0);
    assert(is_less(4, 4) == 0);
    assert(is_less(-5, -3) == 1);
    assert(is_less(-3, -5) == 0);
    assert(is_less(INT_MIN, 1) == 1);
    assert(is_less(1, INT_MIN) == 0);

    printf("All assertions passed!\n");
}
