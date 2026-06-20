#include <stdio.h> 
#include <string.h>

void reverse(char *str, int low, int high);
void swap(char *x, char *y);

int main(void) {
        char str[] = "hello!";
        size_t len = strlen(str);
        reverse(str, 0, len);
        
        printf("%s\n", str);
        return 0;
}

void reverse(char *str, int low, int high) {
        if (low >= high) return;
        
        reverse(str, low + 1, high - 1);
        swap(&str[low], &str[high - 1]);
}

void swap(char *x, char *y) {
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
}
