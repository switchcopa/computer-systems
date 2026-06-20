#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MAX_ITER 1000000

typedef struct {
    bool converges;
    double limit;
    int iterations_needed;
} ConvergenceResult;

ConvergenceResult analyze_convergence(double (*seq)(unsigned long int n)) {
    ConvergenceResult result = {false, 0.0, 0};
    
    // Track last few values
    double values[5];
    int converged_count = 0;
    const double eps1 = 1e-9;
    const double eps2 = 1e-12;
    
    // Multiple convergence criteria
    bool cauchy_criteria_met = false;
    bool monotonic_convergence = false;
    
    for (unsigned long int n = 1; n <= MAX_ITER; n++) {
        double current = seq(n);
        
        // Store last 5 values
        values[n % 5] = current;
        
        // Check Cauchy criterion (simplified)
        if (n >= 5) {
            double max_diff = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = i+1; j < 5; j++) {
                    double diff = fabs(values[i] - values[j]);
                    if (diff > max_diff) max_diff = diff;
                }
            }
            if (max_diff < eps1) {
                cauchy_criteria_met = true;
            }
        }
        
        // Check if essentially zero for exp-like sequences
        if (fabs(current) < eps2) {
            result.converges = true;
            result.limit = 0.0;
            result.iterations_needed = n;
            return result;
        }
        
        // Check monotonic approach to a value
        if (n > 10) {
            double prev = seq(n-1);
            if (fabs(current - prev) < eps1) {
                converged_count++;
                if (converged_count > 100) {
                    result.converges = true;
                    result.limit = current;
                    result.iterations_needed = n;
                    return result;
                }
            } else {
                converged_count = 0;
            }
        }
        
        // Check for obvious divergence
        if (!isfinite(current)) {
            result.converges = false;
            result.iterations_needed = n;
            return result;
        }
    }
    
    // If we get here, we couldn't determine convergence
    // This doesn't mean it diverges - we just don't know
    result.converges = false;  // "Unknown" would be more accurate
    return result;
}

// Test sequences
double seq1(unsigned long int n) { return exp(-n); }
double seq2(unsigned long int n) { return 1.0 / n; }
double seq3(unsigned long int n) { return pow(1 + 1.0/n, n); }  // Should approach e
double seq4(unsigned long int n) { return sin(n); }  // Diverges

int main(void) {
    ConvergenceResult r;
    
    printf("Testing exp(-n):\n");
    r = analyze_convergence(seq1);
    printf("Converges: %s, Limit: %.15f, Iterations: %d\n\n", 
           r.converges ? "yes" : "no", r.limit, r.iterations_needed);
    
    printf("Testing 1/n:\n");
    r = analyze_convergence(seq2);
    printf("Converges: %s, Limit: %.15f, Iterations: %d\n\n", 
           r.converges ? "yes" : "no", r.limit, r.iterations_needed);
    
    return 0;
}
