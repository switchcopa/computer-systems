#include <stdio.h> 
#include <string.h>

void itoa(int n, char s[], unsigned int min_fwidth);
void reverse(char s[]);

int main(void) {
        int x = -13151;
        char buffer[32];

        itoa(x, buffer, 5);
        printf("string: %s\n", buffer);

        return 0;
}

void itoa(int n, char s[], unsigned int min_fwidth) {
        unsigned int num;
        int i, sign, spaces;
        
        if ((sign = n) < 0) 
                num = (unsigned) -n;
        else
                num = n;
        
        i = 0;
        do {
                s[i++] = num % 10 + '0';
        } while ((num /= 10) > 0);
        
        if (sign < 0) 
             s[i++] = '-';

        for (spaces = 0; spaces < min_fwidth; spaces++) 
                s[i++] = ' '; 
        
        s[i] = '\0';
        reverse(s);
}

void reverse(char s[]) {
        int i, j, temp;

        for (i = 0, j = strlen(s) - 1; i < j ;i++, j--) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
        }
}
