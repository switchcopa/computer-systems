
/*
2.73 ◆◆
Write code for a function with the following prototype: */

/* Addition that saturates to TMin or TMax */

/*
int saturating_add(int x, int y);

Instead of overflowing the way normal two’s-complement addition does, sat-
urating addition returns TMax when there would be positive overflow, and TMin
when there would be negative overflow. Saturating arithmetic is commonly used
in programs that perform digital signal processing.
Your function should follow the bit-level integer coding rules (page 164).
*/

#define INT_WIDTH (sizeof(int) << 3)
#define TMIN ((int)(1U << (INT_WIDTH - 1)))
#define TMAX (~TMIN)

int saturating_add(int x, int y)
{
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    unsigned usum = ux + uy;

    int overflow = (int)((~(ux ^ uy) & (ux ^ usum)) >> (INT_WIDTH - 1));

    int overflow_mask = -overflow;
    int sign = x >> (INT_WIDTH - 1);

    int sat_target = TMAX ^ sign;

    return ((int)usum & ~overflow_mask) | (sat_target & overflow_mask);
}

#include <stdio.h>
#include <limits.h>
#include <assert.h>

void main(void)
{   
    assert(saturating_add(0x80000000, 0x80000000)==INT_MIN);
    assert(saturating_add(0x10, 0x20)==0x30);
    assert(saturating_add(0x7FFFFFFF, 0x7FFFFFFF)==INT_MAX);
}
