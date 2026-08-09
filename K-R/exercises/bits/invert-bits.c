#include <stdio.h> 

int invert_bits(unsigned int x, unsigned int pos, unsigned int n);
void debug_bits(unsigned int x);

int main(void) 
{
        unsigned int x, pos, n, result;

        x = 0b10010101, pos = 2, n = 4;

        // should be 10101001
        result = invert_bits(x, pos, n); 
        printf("result: %d, bits: ", result);  

        debug_bits(result); 
        
        return 0;
}

int invert_bits(unsigned int x, unsigned int pos, unsigned int n) 
{
        unsigned int mask = ((1U << n) - 1) << (pos - n + 1);
        printf("mask: ");
        debug_bits(mask);
        
        return x ^ mask; 
}

void debug_bits(unsigned int x) 
{
        for (int i = 31; i >= 0; i--) 
        {
                if ((x & (1 << i)) != 0) 
                        printf("1");
                else printf("0");
        }

        printf("\n");
}
