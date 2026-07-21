
#include <stdint.h>
#include <limits.h>

int tmult_ok(int x, int y)
{
    int64_t x64 = (int64_t)x;
    int64_t y64 = (int64_t)y;

    int64_t p   = x64 * y64;
    return p >= INT_MIN && p <= INT_MAX;
}
