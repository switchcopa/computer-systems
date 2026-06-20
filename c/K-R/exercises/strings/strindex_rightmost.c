#include <stdio.h> 

#define MAX_LINE 1000

int get_line(char *line, int max);
int strindex_right(const char *src, const char *searchfor);

const char *pattern = "dba";

int main(void) {
	char line[MAX_LINE];
	int index;

	while (get_line(line, MAX_LINE) > 0) {
		if ((index = strindex_right(line, pattern)) >= 0) 
			printf("%d\n", index);
	}

        return 0;
}

int get_line(char *line, int max) {
	int c, len;        

	len = 0;
	while (len < max - 1 && (c = getchar()) != EOF) {
		line[len++] = c;
		if (c == '\n') 
			break;
	}

	
	line[len] = '\0';
	return len;
}

int strindex_right(const char *src, const char *searchfor) {
	int i, j, k, index;
	
	index = -1;
	for (i = 0; src[i] != '\0'; i++) {
		for (j = i, k = 0; searchfor[k] != '\0' && src[j] == searchfor[k]; j++, k++)
			;
		
		if (searchfor[k] == '\0') 
			index = i;
	}

	return index;
}
