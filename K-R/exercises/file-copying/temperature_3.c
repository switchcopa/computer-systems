#include <stdio.h> // include the preprocessor directive for I/O 

#define LOWER 300.0f 
#define UPPER 0.0f 
#define STEP 20.0f 

int main() {
    float cels; // declare variable fahrenheit

    for (float fahr = LOWER; fahr >= UPPER; fahr -= STEP) {
        cels = (5.0/9.0) * (fahr - 32.0); 

        printf("%6.2f\t\t%3.2f\n", fahr, cels);
    }

    return 0;
}
