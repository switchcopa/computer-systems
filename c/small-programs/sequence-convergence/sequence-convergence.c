#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define EPSILON 1e-12
#define MAX_ITER 10000000

double a(unsigned int n) {
	return exp(-n);
}

bool is_convergent(double (*seq)(unsigned int n), double *limit);

int main(void) {
        double limit;
        bool converges = is_convergent(a, &limit);

        if (converges)
                printf("The sequence a_n converges.\nIts limit is %.1lf\n", limit);
        else
                printf("The sequence a_n diverges.\n");

	
	return 0;
}

bool is_convergent(double (*seq)(unsigned int n), double *limit) {
	unsigned int i;
        double diff, limit_found;
        unsigned int window = 10;
	bool limit_exists = false;
	int stability = 0, required_stability = 10;	
         
        for (i = 1; i + window < MAX_ITER; i++) {
                diff = fabs(seq(i+window)-seq(i));
		
                if (diff < EPSILON) {
                        limit_found = seq(i);
			limit_exists = true;
			break;
		}

                if (!isfinite(seq(i))) return false;
        }

	if (limit_exists) {
		for (i = 1; i < MAX_ITER; i++)
			if (fabs(seq(i) - limit_found) < EPSILON) {
				stability++;

				if (stability >= required_stability) {
                                        *limit = limit_found;
					return true;
                                }
			} else 
				stability = 0;
	} else 
		return false;
}
