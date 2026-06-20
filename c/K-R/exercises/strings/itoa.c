#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
        int x = INT_MIN;
        char buffer[32]; 
        
        printf("int: %d\n", x);

        itoa(x, buffer);
        printf("%s\n", buffer);

        return 0;
}

void itoa(int n, char s[]) {
        unsigned num;
        int i = 0;
        int sign = n;
        
        if (n < 0) 
                num = - (unsigned int)n;
        else 
                num = n;

        do {
                s[i++] = num % 10 + '0';
        } while ((num /= 10) > 0);

        if (sign < 0)
                s[i++] = '-';
         
        s[i] = '\0';
        reverse(s);
}

void reverse(char s[]) {
        int i, j;

        for (i = 0, j = strlen(s) - 1; i < j ;i++, j--) {
                int temp = s[i];
                s[i] = s[j];
                s[j] = temp;
        }
}
