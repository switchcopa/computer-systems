#include <stdio.h> 

void set_bit(int* x, unsigned char k);
void clear_bit(int* x, unsigned char k);

int main(void) {
        int x, k;

        x = 13; // 1101
        k = 1;
        set_bit(&x, k); // 1111 = 15
        printf("set %dth bit for x: x = %d\n", k, x);
        
        k = 3;
        clear_bit(&x, k); // 0111 =
        printf("set %dth bit for x: x = %d\n", k, x);
        return 0;
}

void set_bit(int* x, unsigned char k) {
        *x |= (1 << k);
}

void clear_bit(int* x, unsigned char k) {
        *x &= ~(1 << k);
}
