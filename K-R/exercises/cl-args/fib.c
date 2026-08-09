#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

unsigned long long int fib(unsigned int);
unsigned int atoull(const char *);
unsigned long long int power(int base, long n);

int 
main(int argc, char **argv)
{
	if (argc != 2) 
	{
		printf("Usage: ./fib <n> to get the nth number of the fibonacci sequence\n");
		return EXIT_FAILURE;
	}
	
	unsigned int n = atoull(argv[1]);
	unsigned long long int f = fib(n);
        printf("%llu\n", f);
	return 0;
}

unsigned long long int fib(unsigned int n)
{
	double root5 = sqrt(5.0);
	
	return (unsigned long long int) ((1.0 / root5) * (power((1.0 + root5) / 2.0, n) - power((1.0 - root5) / 2.0, n)));
}

unsigned int atoull(const char *str)
{
	int i;
	unsigned long long int res = 0;
	
	for (i = 0; isspace(str[i]); i++)
		;
                
        for (; isdigit(str[i]); i++)
                res = 10 * res + (str[i] - '0');

	return res;
}

unsigned long long int power(int base, long n)
{
        unsigned long long int p = 1;

        for (int i = 0; i < n; i++)
                p = p * base;

        return p;
}
