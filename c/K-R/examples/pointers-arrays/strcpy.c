#include <stdio.h>

const char *buff = "hello!\n";

/* str_cpy: copy t to s, array subscript version */
void str_cpy(char *s, const char *t) {
        int i;
        
        i = 0;
        while ((s[i] = t[i]) != '\0')
                i++;
}

int main(void) {
        char arr[10];

        str_cpy(arr, buff);
        printf("%s", arr);
        return 0;
}
