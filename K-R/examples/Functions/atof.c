#include <ctype.h>

double atof(const char *src);

double atof(const char *src) {
	double val, power;
	int i, sign;

	for (i = 0; isspace(src[i]); i++)
		;

	sign = (src[i] == '-') ? -1 : 1;
	if (src[i] == '+' || src[i] == '-')
		i++;

	for (val = 0.0; isdigit(src[i]); i++) 
		val = 10.0 * val + (src[i] - '0');

	if (src[i] == '.') 
		i++;

	for (power = 1.0; isdigit(src[i]); i++) {
		val = 10.0 * val + (src[i] - '0');
		power *= 10.0;
	}
		
	return sign * val / power;
}
