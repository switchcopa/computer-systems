#include <stdio.h>

#define MAX_LINE 1000
#define BUF_SIZE 256

int get_line(char *restrict line, int size);
void strn_cpy(char *restrict dest, const char *restrict src, int n);

int main(void) {
	char longest[MAX_LINE];
	char line[BUF_SIZE];
	
	int buf_len = 0, max_len = 0;
	while ((buf_len = get_line(line, BUF_SIZE)) > 0) {
		if (buf_len > max_len) {
			max_len = buf_len;
			strn_cpy(longest, line, buf_len);
		}			
	}
	
	if (max_len > 0) {
		printf("%s", longest); 
	}
	return 0;
}

int get_line(char *restrict line, int size) {
	int c, len = 0;
	
	while ((c = getchar()) != EOF && len < size - 1) {
			line[len++] = c;
		if (c == '\n')
			break;
	}

	line[len] = '\0';
	if (c == EOF && len == 0)
		return -1;
	return len;	
}

void strn_cpy(char *restrict dest, const char *restrict src, int n) {
	int i;
	
	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}
