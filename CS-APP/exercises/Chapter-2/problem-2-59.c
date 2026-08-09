
#include <stdio.h>
#include <stdint.h>

int32_t lsb_and_remaining(int32_t x, int32_t y)
{
    return (x & 0xFF) | (y & ~(int32_t)0xFF);
}

void main(void)
{
    int32_t x = 0x89ABCDEF;
    int32_t y = 0x76543210;
    printf("%X\n", lsb_and_remaining(x, y));
}
