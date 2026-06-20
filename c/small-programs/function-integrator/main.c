
// NOTE: This program does not check for discontinuities of a real function

#include <stdio.h>
#include <math.h>

#define N 1000
#define PI 3.14159265358979323846
#define EPS 10e-3

double f(double x);
double integral(double (*f)(double), double a, double b);

int main(void) {
	double res = integral(&f, 0, 1);
	if (fabs(res) <= EPS)
		printf("0\n");
	else
		printf("%.4f\n", res);

	return 0;
}

double f(double x) {
	return exp(pow(x, 2));
}

double integral(double (*f)(double), double a, double b) {
	double delta_n = (double)(b-a) / N;
	double sum = 0.5 * (f(a) + f(b));

	for (int k = 1; k < N; k++) {
		sum += f(a + k * delta_n);

		if (!isfinite(sum))
			return sum;
	}

	return sum * delta_n;
}
