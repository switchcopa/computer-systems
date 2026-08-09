#include <stdio.h> 

#define MAX_ARRAY_SIZE 100

void escape(char dest[], char src[], size_t bytes);
void reverse_escape(char dest[], char src[], size_t bytes);

int main(void) {
        /*
        "        hello
        this text is not important \
        "
        */
        char arr[] = "\thello\nthis text is not important \\\n"; 
        char dest[MAX_ARRAY_SIZE];

        size_t bytes = sizeof(arr) / sizeof(char);

        escape(dest, arr, bytes);
//        printf("%s\n", dest);
        
        char dest_reverse[MAX_ARRAY_SIZE];
        reverse_escape(dest_reverse, dest, MAX_ARRAY_SIZE);
        
        printf("%s\n", dest_reverse);
        
        return 0;
}

void escape(char dest[], char src[], size_t bytes) {
        char c;
        int k;

        for (int i = k = 0; i < bytes && src[i] != '\0'; i++) {
                c = src[i];

                switch (c) {
                        case '\\':
                                dest[k++] = '\\';
                                dest[k++] = '\\';
                                break;
                        case '\n':
                                dest[k++] = '\\';
                                dest[k++] = 'n';
                                break;
                        case '\t':
                                dest[k++] = '\\';
                                dest[k++] = 't';
                                break;
                        default: 
                                dest[k++] = c;
                                break;
                }
        }

        dest[k] = '\0';
}

void reverse_escape(char dest[], char src[], size_t bytes) {
        int c, k, next;

        for (int i = k = 0; i + 1 < bytes && src[i + 1] != '\0'; i++) {
                c = src[i];

                switch (c) {
                        case '\\':
                                next = src[++i];

                                switch (next) {
                                        case 'n':
                                                dest[k++] = '\n';
                                                break;
                                        case 't':
                                                dest[k++] = '\t';
                                                break;
                                        case '\\':
                                                dest[k++] = '\\';
                                                break;
                                        default:
                                                break;
                                }

                                break;

                        default:
                                dest[k++] = c;
                                break;
                }
        }

        dest[k] = '\0';
}
