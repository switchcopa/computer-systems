#include <stdio.h> 

void itoa_helper(char *str_buff, int x, int *index);
void itoa(char *str_buff, int x, int *index);

int main(void) {
        char buffer[100];
        int x = -1342;
        int index = 0;
        int *p = &index;
        
        itoa(buffer, x, p);
        printf("%s\n", buffer);
        return 0;
}

void itoa_helper(char *str_buff, int x, int *index) {
        if (x == 0) return;

        itoa_helper(str_buff, x / 10, index);
        
        str_buff[(*index)++] = (x % 10) + '0';
}

void itoa(char *str_buff, int x, int *index) {
        if (x == 0) {
                str_buff[(*index)++] = '0';
                str_buff[*index] = '\0';
                return;
        }
        
        if (x < 0) {
                str_buff[(*index)++] = '-';
                x = -x;
        }
        
        itoa_helper(str_buff, x, index);
        str_buff[*index] = '\0';
}
