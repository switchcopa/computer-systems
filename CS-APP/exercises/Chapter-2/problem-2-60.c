
/*

Suppose we number the bytes in a w-bit word from 0 (least significant) to w/8 −1
(most significant). Write code for the following C function, which will return an
unsigned value in which byte i of argument x has been replaced by byte b:

unsigned replace_byte (unsigned x, int i, unsigned char b);
Here are some examples showing how the function should work:

replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB

*/

#include <stdio.h>
#include <stdint.h>

/* replace the i-th byte of the 32 bit unsigned integer x with the byte b*/
uint32_t replace_byte(uint32_t x, int i, uint8_t b)
{
    uint32_t shift = i << 3;
    return (x & ~((uint32_t)0xFF << shift)) | ((uint32_t)b << shift);
}

void main(void)
{
    uint32_t x = 0x12345678;
    printf("%X\n", replace_byte(x, 2, 0xAB));
    printf("%X\n", replace_byte(x, 0, 0xAB));
}
