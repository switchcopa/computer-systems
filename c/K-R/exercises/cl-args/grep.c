#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 2048
#define MAX_LINE 1028

int get_line(char *line, int max_lines);
int has(const char *src, const char *pattern);

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./grep \"pattern\"\n");
		return EXIT_FAILURE;
	}
		
	const char *pattern = argv[1];
	char *buff[BUF_SIZE];
	char line[MAX_LINE];
	int lines[BUF_SIZE] = {0};
	int len;
	int line_num = 1;
	int bufp = -1;

	for (int i = 0; i < BUF_SIZE; i++)
		buff[i] = NULL;

	while ((len = get_line(line, MAX_LINE)) > 0 && bufp < BUF_SIZE) {
		if (has(line, pattern) == 1) {
			buff[++bufp] = malloc(sizeof(char) * MAX_LINE);
                        if (buff[bufp] == NULL) {
                                fprintf(stderr, "failed to allocate memory for string\n");
                                return EXIT_FAILURE;
                        }

			strcpy(buff[bufp], line);
			lines[bufp] = line_num;
		}

		line_num++;
	}
	
	for (int i = 0; i <= bufp; i++) {
		printf(" %-5d | %s", lines[i], buff[i]);
		free(buff[i]);
	}

	return EXIT_SUCCESS;
}

int get_line(char *line, int max_lines) {
	int len = 0;
	int c;
	
	while ((c = getchar()) != EOF && len < max_lines - 1) {
		line[len++] = c;
		if (c == '\n')
			break;	
	}

	if (c == EOF && len == 0)
		return -1;

	line[len] = '\0';
	return len;
}

int has(const char *src, const char *pattern) {
	for (int i = 0; src[i] != '\0'; i++) {
                int k = 0;
		for (int j = i; pattern[k] != '\0' && pattern[k] == src[j]; k++, j++)
			;

		if (k > 0 && pattern[k] == '\0' )
			return 1;
	}

	return 0;
}
