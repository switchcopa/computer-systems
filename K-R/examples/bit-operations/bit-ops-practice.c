#include <stdio.h> 
#include <stdlib.h>

char* get_binary(int x);

int main(void) {
	int x;

	x = 5381;
	char* b = get_binary(x);
	printf("%s\n", b);

	free(b);
	return 0;
}

char* get_binary(int x) {
	int i, bits;
	char* b;
	
	bits = sizeof(int) * 8, i = bits - 1; 
	b = malloc(bits + 1);
	if (!b) {
		printf("failed to allocate memory for buffer\n");
		exit(1);
	}	
        
        for (; i >= 0; i--) {
                b[i] = (x & 1) + '0';
                x >>= 1;
        }
        
        b[bits] = '\0';
        return b;
}
