#include <stdio.h> 
#include <ctype.h>
#include <math.h>

double atof(const char *s);

int main(void) {
        const char* s = "-3.1415e-5"; 
        double r = atof(s); 
        
        printf("%.10f\n", r);
        return 0;
}

double atof(const char *s) {
        double val, power;
        int i, sign, exponent, exponent_sign;
        
        for (i = 0; isspace(s[i]); i++)
                ;
        
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-' || s[i] == '+')
                i++;

        for (val = 0.0; isdigit(s[i]); i++) 
                val = 10.0 * val + (s[i] - '0');

        if (s[i] == '.') 
                i++;

        for (power = 1.0; isdigit(s[i]); i++) {
                val = 10.0 * val + (s[i] - '0');
                power *= 10.0;
        }

        if (s[i] == 'e' || s[i] == 'E') 
                i++;

        exponent_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-' || s[i] == '+')
                i++;

        for (exponent = 0; isdigit(s[i]); i++) 
                exponent = 10 * exponent + (s[i] - '0');

        return sign * (val / power) * pow(10, exponent * exponent_sign);
}
