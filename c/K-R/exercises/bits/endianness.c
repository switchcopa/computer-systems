#include <stdio.h>

int main(void) {
	unsigned int x = 0x12345678;
	unsigned char *p = (unsigned char*)&x;
	
	if (p[0] == 0x12)
		printf("Machine is Big-Endian\n");
	else 
		printf("Machine is Litte-Endian\n");
	
	return 0;
}
