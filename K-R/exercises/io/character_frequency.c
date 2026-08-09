#include <stdio.h>
    
int main() {
    int count[256] = {0};

    int c;
    while ((c = getchar()) != EOF) {
        count[c]++;        
    }
    
    int i;
    for (i = 0; i < 256; i++) {
        if (count[i] == 0) continue;

        else if (i == '\n') {
            printf("\\n: %d\n", count[i]);
            continue;
        }

        else if (i == '\t') { 
            printf("\\t: %d\n", count[i]);
            continue;
        }

        printf("%c: %d\n", i, count[i]);
    }
    
    return 0;
}
