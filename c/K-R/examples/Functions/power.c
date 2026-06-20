#include <stdio.h>

int power(int base, int n) {
    int p; 
    
    p = 1;
    for (int i = 1; i <= n; i++) {
        p = p * base; 
    }

    return p;
}

int main() {
    printf("2 to the power of 3 is: %d\n", power(2,3));
    printf("-3 to the power of 2 is: %d\n", power(-3, 2));

    return 0;
}
