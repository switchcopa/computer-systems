
/*
2.74 ◆◆
Write a function with the following prototype:
*/

/* Determine whether arguments can be subtracted without overflow */

/*
int tsub_ok(int x, int y);

This function should return 1 if the computation x-y does not overflow.
*/

__attribute__((optimize("O3")))
int tsub_ok(int x, int y) {
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    unsigned usub = ux - uy;

    int shift = (sizeof(int) << 3) - 1;

    int sx = ux >> shift & 1;
    int sub_sign = usub >> shift & 1;
    int diff_sign = (ux ^ uy) >> shift & 1;

    int overflow = diff_sign & (sx ^ sub_sign);

    return !overflow;
}

/*
(x, y) = (INT_MAX, -1)
usub = (unsigned)x - (unsigned)y
shift = 31

sx = 0
sub_sign = usub >> shift & 1 = 1
diff_sign = 1

return 1 & ((1 & !0) | (!1 & 0))
*/

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>

static int ref_tsub(int x, int y) {
    int64_t diff = (int64_t)x - (int64_t)y;
    return (diff >= INT_MIN) && (diff <= INT_MAX);
}

void main(void) {
    /* 1. Same signs (Must NEVER overflow) */
    assert(tsub_ok(100, 50) == ref_tsub(100, 50));
    assert(tsub_ok(-100, -50) == ref_tsub(-100, -50));
    assert(tsub_ok(INT_MAX, INT_MAX) == ref_tsub(INT_MAX, INT_MAX));
    assert(tsub_ok(INT_MIN, INT_MIN) == ref_tsub(INT_MIN, INT_MIN));

    /* 2. Zero edge cases */
    assert(tsub_ok(0, 0) == ref_tsub(0, 0));
    assert(tsub_ok(INT_MAX, 0) == ref_tsub(INT_MAX, 0));
    assert(tsub_ok(INT_MIN, 0) == ref_tsub(INT_MIN, 0));
    assert(tsub_ok(0, INT_MIN) == ref_tsub(0, INT_MIN));

    /* 3. Opposite signs - Safe (No overflow) */
    assert(tsub_ok(50, -100) == ref_tsub(50, -100));
    assert(tsub_ok(-50, 100) == ref_tsub(-50, 100));
    assert(tsub_ok(0, 50) == ref_tsub(0, 50));
    assert(tsub_ok(0, -50) == ref_tsub(0, -50));

    /* 4. Opposite signs - Positive overflow boundaries (TMax) */
    assert(tsub_ok(INT_MAX - 5, -5) == ref_tsub(INT_MAX - 5, -5));
    assert(tsub_ok(INT_MAX - 5, -6) == ref_tsub(INT_MAX - 5, -6));
    assert(tsub_ok(INT_MAX, -1) == ref_tsub(INT_MAX, -1));
    assert(tsub_ok(INT_MAX, INT_MIN) == ref_tsub(INT_MAX, INT_MIN));

    /* 5. Opposite signs - Negative overflow boundaries (TMin) */
    assert(tsub_ok(INT_MIN + 5, 5) == ref_tsub(INT_MIN + 5, 5));
    assert(tsub_ok(INT_MIN + 5, 6) == ref_tsub(INT_MIN + 5, 6));
    assert(tsub_ok(INT_MIN, 1) == ref_tsub(INT_MIN, 1));
    assert(tsub_ok(INT_MIN, INT_MAX) == ref_tsub(INT_MIN, INT_MAX));

    printf("All tsub_ok asserts passed successfully!\n");
}
