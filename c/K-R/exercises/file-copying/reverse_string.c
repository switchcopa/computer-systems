#include <stdio.h>

#define BUF_SIZE 256

void reverse(char *str_buf, int size);
int get_line(char *restrict line, int size);

int main(void) {
	char line[BUF_SIZE];
	int len;
	while ((len = get_line(line, BUF_SIZE)) > 0) {
		reverse(line, len);
		printf("%s\n", line);
	}
	
	return 0;
}

int get_line(char *restrict line, int size) {
	int c, len = 0;
	
	while ((c = getchar()) != EOF && len < size - 1) {
		if (c == '\n')
			break;

		line[len++] = c;
	}

	line[len] = '\0';
	if (c == EOF && len == 0)
		return -1;
	return len;	
}

void swap(char *s, char *t) {
	*s = *s ^ *t;
	*t = *s ^ *t;
	*s = *s ^ *t;
}

void reverse(char *str_buf, int size) {
	int i;
	
	for (i = 0; i < size / 2; i++)
		swap(&str_buf[i], &str_buf[size-i-1]);
}

