#include <string.h>
#include <stdio.h>
#include <stdint.h>
/* itoa: convert n to character in s */
void reverse(char s[]);
void itoa(int n, char s[]);

int main(void) {
        signed int n = -INT32_MAX;
        char s[20]; 
        
        printf("integer: %d\n", n);
        itoa(n, s); 
        
        printf("%s\n", s);
        return 0;
}

void itoa(int n, char s[]) {
        int i, sign;
        
        if ((sign = n) < 0) 
                n = -n;
        
        i = 0;                
        do {
                s[i++] = n % 10 + '0'; 
        } while ((n /= 10) > 0);

        if (sign < 0) 
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

void reverse(char s[])
{
        int c, i, j;
        for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}
