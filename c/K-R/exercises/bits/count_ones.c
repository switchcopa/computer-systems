#include <stdio.h>
#include <stdlib.h>

int count_ones(int x);
char* bit(int x);

int main(void) {
        int x;
        x = 101;  
        char* bits = bit(x);
        printf("%s\n", bits); 
        printf("Number of ones:%d\n", count_ones(x));

        free(bits);
        return 0;
}

int count_ones(int x) {
        int count;
        count = 0;

        while (x) {
                count += x & 1; 
                x >>= 1;
        }

        return count;
}

char* bit(int x) {
        int k;
        size_t size;
        
        size = 32 + 1; // bits + null terminator + spaces
        char* bits = malloc(sizeof(char) * size);
        if (!bits) {
                printf("failed to allocate bits buffer\n");
                return NULL;
        }
        
        bits[size - 1] = '\0';
        for (k = 31; k >= 0; k--) 
                bits[31 - k] = (x & (1U << k)) ? '1' : '0';

        return bits;
}
