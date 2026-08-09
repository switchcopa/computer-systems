#include <stdio.h> 
#include <string.h>

void itob(int n, char s[]);
void reverse(char s[]);

int main(void) {
        int n = 166;
        char s[20];

        itob(n, s);
        printf("test hexadecimal: %X\n", n);
        printf("string: %s\n", s);

        return 0;
}

void itob(int n, char s[]) {
        int i, remainder, sign;
        unsigned int num;

        if ((sign = n) < 0) {
                num = (unsigned int) -n;
        } else {
                num = (unsigned int) n;
        }

        i = 0;
        do {
                remainder = num % 16;

                if (remainder < 10) 
                        s[i++] = (char) remainder + '0';
                else 
                        s[i++] = (char) remainder + 'A' - 10;

        } while ((num /= 16) > 0);

        s[i] = '\0';
        reverse(s);
}

void reverse(char s[]) {
        int i, j;
        char temp;

        for (i = 0, j = strlen(s) - 1; i < j ; i++, j--) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
        }
}