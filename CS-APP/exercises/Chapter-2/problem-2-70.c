
/*
* Return 1 when x can be represented as an n-bit, 2’s-complement
* number; 0 otherwise
* Assume 1 <= n <= w
*/

int fits_bits(int x, int n)
{
    int shift = 32 - n;
    int y     = (x << shift) >> shift;

    return !(x ^ y);
}

#include <stdio.h>

void main(void)
{
    printf("%d\n", fits_bits(-5, 8));
    printf("%d\n", fits_bits(200, 8));
}
