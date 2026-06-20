#include <stdio.h> 

int get_bit(int x, unsigned int k);

int main(void) {
        int x, n;
        unsigned int k;
 
        x = 11; // 1011 = 11
        k = 4;
        
        n = get_bit(x, k);
        printf("%d", n);
        return 0;
}

int get_bit(int x, unsigned int k) {
        return (x & (1 << k)) != 0;
}
