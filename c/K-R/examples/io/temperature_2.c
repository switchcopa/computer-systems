#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20 

int main() {
    float cels;

    for (int fahr = LOWER; fahr <= UPPER; fahr += STEP) {
        cels = (5.0/9.0) * (fahr - 32.0);
        printf("%3d\t%6.2f\n", fahr, cels);
    }
    
    return 0;
}
