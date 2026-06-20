#include <stdio.h> 

int get_bit(int x, unsigned int k);
void set_bit(int* x, unsigned int k);
void clear_bit(int *x, unsigned int k);
void toggle_bit(int *x, unsigned int k);

int main(void) {
        int x,k,n;
        x = 13; // 1101
        k = 2;

        n = get_bit(x, k); 
        printf("the %dth bit of x is: %d\n", k, n);
        
        k = 1;
        set_bit(&x, k); // 1111
        printf("set %dth bit of x: x = %d\n", k, x);

        k = 3;
        clear_bit(&x, k); // 0111
        printf("cleared %dth bit of x: x = %d\n", k, x);

        k = 0;
        toggle_bit(&x, k);
        printf("toggled %dth bit of x: x = %d\n", k, x);
}

int get_bit(int x, unsigned int k) {
        return (x & (1U << k)) != 0;
}

void set_bit(int* x, unsigned int k) {
        *x |= (1U << k);
}

void clear_bit(int *x, unsigned int k) {
        *x &= ~(1U << k);
}

void toggle_bit(int *x, unsigned int k) {
        *x ^= (1U << k);
}
