#include <stdio.h>

/* the problem says: write a function setbits, that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.*/

unsigned setbits(unsigned int x, int pos, int n, int y);

int main(void) {
        unsigned int x, y, pos, n, z, result; 
        x = 167, y = 30;  // 1010 0111 and 0001 1110
        n = 3, pos = 5; 
        
        printf("%u\n", setbits(x, pos, n, y));
        return 0;
}

unsigned setbits(unsigned int x, int pos, int n, int y) {
        unsigned mask, ybits, xcleared; 

        mask = ~(~0 << n);
        ybits = (y & mask) << (pos + 1 - n);
        xcleared = x & ~(mask << (pos + 1 - n));

        return xcleared | ybits;
}
