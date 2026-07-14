
/*
Write a function with the following prototype:

// Determine whether arguments can be added without overflow 
int uadd_ok(unsigned x, unsigned y);

This function should return 1 if arguments x and y can be added without
causing overflow.
*/

#include "stdint.h"

int uadd_ok(uint32_t x, uint32_t y)
{
    uint32_t result = x + y;
    return result < x;
}
