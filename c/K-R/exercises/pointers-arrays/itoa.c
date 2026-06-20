#include <stdio.h> 

void itoa(char *arr, int n);

int main(void) {
        char arr[10];
        itoa(arr, -1512351);
        printf("%s\n", arr);

	return 0;
}

void itoa(char *arr, int n) {
	int sign;
	if (n < 0) {
		sign = -1;
		n = -n;
		*arr++ = '-';
	} else sign = 1;

	do {
		*arr++ = n % 10 + '0';
	} while ((n /= 10) > 0);

        *arr = '\0';
}
