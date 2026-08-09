#include <stdio.h>

/* formula for celsius to farenheit conversion: 
   c = 5 * (f - 32) / 9
   
   objective: 
   print celsius-farenheit table for F = 0, 20, ..., 300 
*/

int main() {
    float lower, upper, step;
    float fahr, cels;
        
    lower = 0, upper = 300, step = 20;
    fahr = lower;
    
    printf("%3s\t%6s\n%3s\t%6s\n", "Fahr", "Cels", "----", "----");
    while (fahr <= upper) {
        cels = (5.0/9.0) * (fahr - 32.0); 
        printf("%3.0f\t%6.3f\n", fahr, cels);
        fahr += step;
    }

    return 0;
}
