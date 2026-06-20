#include <stdio.h> 
/* getbits: get n bits from position p */

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

int main(void) {
    unsigned x, res; 
    int p, n;
    
    x = 0b11110110; // 246 in decimal
    p = 4, n = 3; 
    
    res = getbits(x, p, n); 
    printf("Result: %d\n", res);

    return 0;
}
