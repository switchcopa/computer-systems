#include <stdio.h>

unsigned int getbits(int x, unsigned pos, unsigned n);

int main(void) {
        int x;
        unsigned int y, pos, n;
        
        x = 21; // 0001 0101
        pos = 3, n = 3;
        y = getbits(x, pos, n);

        printf("%d", y); // should print 2 
        return 0;
}

unsigned int getbits(int x, unsigned pos, unsigned n) {
        if (pos < n - 1) {
                printf("Index out of bounds\n");
                return 0;
        }

        signed int mask, ex;
                
        mask = ~(~0U << n);
        ex = x >> (pos - n + 1);

        return mask & ex;
}
