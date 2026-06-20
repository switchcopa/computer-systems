#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define STACK_SIZE 256
#define FILE_BUF_SIZE 16384

typedef enum {
	IN_COMMENTS,
	IN_MULTI_COMMENT,
	NONE
} comm_state;

typedef enum {
	IN_QUOTES,
	IN_DOUBLE_QUOTES,
	Q_NONE
} quote_state;

typedef struct {
	int line;
	char bracket;
} stack_entry;

bool endswith(const char *restrict buf, const char *restrict suffix);
char *load_file(const char *restrict filename, size_t *out_size);
void push(stack_entry entry);
stack_entry pop(void);
bool is_empty(void);
bool is_opening_bracket(char c);
bool is_closing_bracket(char c);
bool is_matching_brackets(char c, char t);

stack_entry synt_st[STACK_SIZE];
int stp = -1;

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: ./syn-c file.c\n");
		return EXIT_FAILURE;
	}
		
	if (!endswith(argv[1], ".c")) {
		printf("file '%s' is not of extension '.c'\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	size_t f_size;	
	char *file_buf = load_file(argv[1], &f_size);
	if (file_buf == NULL)
		exit(EXIT_FAILURE);
	
	comm_state st = NONE;
	quote_state qst = Q_NONE;
	size_t file_p = 0;
	int backslashes = 0, nlines = 1;
	
	for (; file_p < f_size; file_p++) {
		if (file_buf[file_p] == '\n')
			nlines++;

		if ((st == IN_COMMENTS && file_p + 1 < f_size && file_buf[file_p] == '\n') ||
			(st == IN_MULTI_COMMENT && file_p + 1 < f_size && file_buf[file_p] == '*' && file_buf[file_p + 1] == '/')) {
			file_p++;
			st = NONE;
		}
		
		if ((qst == IN_QUOTES && file_buf[file_p] == '\'')  ||
				(qst == IN_DOUBLE_QUOTES && file_buf[file_p] == '\"')) {
				if (backslashes == 0 || backslashes % 2 != 0) {
						backslashes = 0;
						qst = Q_NONE;
						continue;
				}
				else {
						backslashes = 0;
						continue;
				}
		} else if ((qst == IN_QUOTES && file_buf[file_p] == '\\') ||
				(qst == IN_DOUBLE_QUOTES && file_buf[file_p] == '\\')) {
				backslashes++;
				continue;
		}

		if (st == IN_COMMENTS || st == IN_MULTI_COMMENT || qst == IN_QUOTES || qst == IN_DOUBLE_QUOTES)
			continue;

		if (file_p + 1 < f_size && file_buf[file_p] == '/' && file_buf[file_p + 1] == '/') {
			st = IN_COMMENTS;
			continue;
		}

		else if (file_p + 1 < f_size && file_buf[file_p] == '/' && file_buf[file_p + 1] == '*') {
			st = IN_MULTI_COMMENT;
			continue;
		}

		if (file_buf[file_p] == '\'') {
			qst = IN_QUOTES;
			continue;
		} else if (file_buf[file_p] == '\"') {
			qst = IN_DOUBLE_QUOTES;
			continue;
		}

		if (is_opening_bracket(file_buf[file_p])) {
			stack_entry entry;
			entry.line = nlines, entry.bracket = file_buf[file_p];
			push(entry);
		}

		else if (is_closing_bracket(file_buf[file_p])) {
			if (is_empty()) {
				fprintf(stderr, "unexpected closing bracket '%c' at line %d\n", file_buf[file_p], nlines);
				continue;
			}

			stack_entry temp = pop();
			if (!is_matching_brackets(temp.bracket, file_buf[file_p])) {
				fprintf(stderr, "syntax error: expected to close bracket '%c' at line %d\n", temp.bracket, temp.line);
				continue;
			}
		}
	}

	while (!is_empty()) {
		stack_entry temp = pop();
		fprintf(stderr, "syntax error: expected to close bracket '%c' at line %d\n", temp.bracket, temp.line); 
	}

	free(file_buf);	
	return EXIT_SUCCESS;
}

void push(stack_entry entry) {
	if (stp >= STACK_SIZE - 1) {
		fprintf(stderr, "pushed to full stack\n");
		exit(EXIT_FAILURE);
	} else
		synt_st[++stp] = entry;
}

stack_entry pop(void) {
	if (stp < 0) {
		fprintf(stderr, "pop from empty stack\n");
		exit(EXIT_FAILURE);
	} else
		return synt_st[stp--];
}

bool endswith(const char *restrict buf, const char *restrict suffix) {
	size_t buf_len = strlen(buf);
	size_t suffix_len = strlen(suffix);

	if (buf_len < suffix_len)
		return false;
	
	return strcmp(buf + (buf_len - suffix_len), suffix) == 0; 
}

char *load_file(const char *restrict filename, size_t *out_size) {
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "failed to load file '%s'\n", filename);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (size >= FILE_BUF_SIZE) {
		fprintf(stderr, "file size too big\n");
		fclose(fp);
		return NULL;
	}
	
	char *buffer = malloc(size + 1);
	if (!buffer) {
		printf("failed to allocate memory for buffer\n");
		fclose(fp);
		return NULL;
	}

	size_t n = fread(buffer, sizeof (char), size, fp);
	if (n < size && ferror(fp)) {
			fprintf(stderr, "an error occured while reading the file's contents\n");
			fclose(fp);
			return NULL;
	}

	buffer[size] = '\0';
	fclose(fp);
	
	if (out_size) 
		*out_size = size;
	return buffer;
}

bool is_opening_bracket(char c) {
	return c == '(' || c == '[' || c == '{';
}

bool is_matching_brackets(char c, char t) {
	return (c == '(' && t == ')') || (c == '[' && t == ']') || (c == '{' && t == '}');
}

bool is_empty(void) {
	return stp == -1;
}

bool is_closing_bracket(char c) {
	return c == ')' || c == ']' || c == '}';
}
