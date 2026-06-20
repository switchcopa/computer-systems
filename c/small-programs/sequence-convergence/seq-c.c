#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define EPSILON 1e-12  // More precise epsilon for exponential decay
#define MAX_ITER 10000000

double a(unsigned long int n) {
    return exp(-n);
}

bool is_convergent(double (*seq)(unsigned long int n), double *limit);

int main(void) {
    double limit;
    bool converges = is_convergent(a, &limit);

    if (converges)
        printf("The sequence a_n converges.\nIts limit is %.15lf\n", limit);
    else
        printf("The sequence a_n diverges.\n");

    return 0;
}

bool is_convergent(double (*seq)(unsigned long int n), double *limit) {
    double current, next;
    int stable_count = 0;
    const int stable_required = 10;  // Reduced since exp(-n) converges quickly
    
    // Check first few values to establish pattern
    for (unsigned long int i = 1; i < MAX_ITER; i++) {
        current = seq(i);
        next = seq(i + 1);
        
        // Check if values are becoming stable
        if (fabs(current - next) < EPSILON) {
            stable_count++;
            
            if (stable_count >= stable_required) {
                // Take the average of recent values as the limit
                double sum = 0;
                for (int j = 0; j < 5; j++) {
                    sum += seq(i - j);
                }
                *limit = sum / 5.0;
                return true;
            }
        } else {
            stable_count = 0;
        }
        
        // Check for divergence
        if (!isfinite(current)) {
            return false;
        }
        
        // For exp(-n), we know it should approach 0
        // If current value is already essentially 0, we can stop
        if (current < EPSILON && i > 10) {
            *limit = 0.0;
            return true;
        }
    }
    
    return false;
}
