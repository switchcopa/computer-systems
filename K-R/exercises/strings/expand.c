#include <stdio.h> 
#include <ctype.h>
#include <string.h>
void expand(const char* s1, char* s2);

int main(void) {
        const char s1[] = "a-d0-3x-z";
        char s2[100];

        expand(s1, s2);
        printf("Expanded: %s\n", s2); 

        return 0;
}

void expand(const char* s1, char* s2) {
        if (strlen(s1) == 0) return;

        int i = 0, j = 0;
        char end, start, dash;

        while (s1[i] != '\0') {
                if (s1[i] != '-' || i == 0 || s1[i+1] == '\0') {
                        s2[j++] = s1[i++];
                        continue;
                }

                start = s1[i-1];
                end = s1[i+1];

                if ((isdigit(start) && isdigit(end) && start <= end) ||
                    (islower(start) && islower(end) && start <= end) || 
                    (isupper(start) && isupper(end) && start <= end)) {
                        
                        for (char c = start + 1; c <= end; c++) 
                                s2[j++] = c;

                        i += 2;
                } else {
                        s2[j++] = s1[i++];
                }
        }

        s2[j] = '\0';
}
