#include <stdio.h> 

void toggle_bit(int* x, unsigned int k);

int main(void) {
        int x = 5; //// this should be 0101 
        toggle_bit(&x, 3);
        
        printf("x after: %d\n", x); // should be 1101 = 13
        return 0;
}

void toggle_bit(int* x, unsigned int k) {
        *x ^= (1 << k);
} 
