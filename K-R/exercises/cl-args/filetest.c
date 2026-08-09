#include <stdio.h>

int main(void) {
	/* there should be no errors */
	int a = 0;
	char b = 'a';
	char c = 'c';
	char arr[100]; // test test
	/* this is a nested
		multi line comment */ 

	printf("Hello world!\n");

	if (0) {
		//nothing 
	}
	
	for (int i = 0; i < 100; i++) {
		arr[i] = 'x';	
	};

	printf("Escaped \n");
	return 0;
}
