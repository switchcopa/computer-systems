#include <stdio.h> 

#define MAX_LINE 1000

int get_line(char line[], unsigned int max);
int strindex(const char *src, const char *searchfor);

const char* pattern = "ould";

int main(void) {
	char line[MAX_LINE];
        int found = 0;

	while (get_line(line, MAX_LINE) > 0) 
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}

	return found;	
}

int get_line(char line[], unsigned int max) {
	int len, c;

	len = 0;
        
        while (len < max - 1 && (c = getchar()) != EOF) {
                line[len++] = c;
                if (c == '\n') 
                	break;
        }

	line[len] = '\0';
	return len;
}

int strindex(const char *src, const char *searchfor) {
	int i, j, k;

	for (i = 0; src[i] != '\0'; i++) {
		for (j = i, k = 0; searchfor[k] != '\0' && src[j] == searchfor[k]; j++, k++) 
			;
		if (k > 0 && searchfor[k] == '\0') 
			return i;
        }

	return -1;
}
