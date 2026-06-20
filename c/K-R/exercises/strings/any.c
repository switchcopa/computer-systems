#include <stdio.h> 
#include <stdbool.h>

int any(char s1[], char s2[]);
char *strp_brk(const char *s1, const char *s2);

int main(void) {
    char s1[] = "hello";
    char s2[] = "world";

    int i = any(s1, s2);
    printf("%d\n", i);    

    return 0;
}

int any(char s1[], char s2[]) {
    int i; 
    bool seen[256] = {false};

    for (i = 0; s2[i] != '\0'; i++) 
        seen[(unsigned char)s2[i]] = true;

    for (i = 0; s1[i] != '\0'; i++) 
        if (seen[(unsigned char)s1[i]]) 
            return i;
    
    return -1;
}

char *strp_brk(const char *s1, const char *s2) {
	int i;
	char *p;
	bool seen[256] = {false};

	for (i = 0; s2[i] != '\0'; i++)
		seen[(unsigned char) s2[i]] = true;

	for (i = 0; s1[i] != '\0'; i++)
		if (seen[(unsigned char) s1[i]]) {
			p = &s1[i];
			return p;
		}

	return NULL;	
}
