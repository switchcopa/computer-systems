#include <stdio.h> 

int main(void) {
    printf("The size of a double is: %zu\n", sizeof(double));
    printf("The size of a long double is: %zu\n\n", sizeof(long double));
    printf("The size of a long int is: %zu\n", sizeof(long int));    
    printf("The size of a unsigned long int is: %zu\n", sizeof(unsigned long int));
    printf("The size of a long long int is: %zu\n", sizeof(long long int)); 
    printf("The size of a unsigned long long int is: %zu\n", sizeof(unsigned long long int));
    printf("The size of a int is: %zu\n", sizeof(int));
    printf("The size of a unsigned int is: %zu\n\n", sizeof(unsigned int));
    printf("The size of a char is: %zu\n", sizeof(char));
    printf("The size of a unsigned char is: %zu\n\n", sizeof(unsigned char));
    printf("The size of a float is: %zu\n\n", sizeof(float));
    printf("The size of a pointer is: %zu\n\n", sizeof(void*));
    printf("The size of a short int is: %zu\n", sizeof(short int));
    return 0;
}
