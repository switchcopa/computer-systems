
/* tail: print the last n lines of the input,
 * by default n is 10
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define _BUF_SIZE 8192U
#define DEFAULT_LINES 10U

int get_line(char *restrict line, size_t n);
uint16_t strtoui(const char *restrict start, char **restrict end);

int main(int argc, char **argv) {
	uint16_t n = DEFAULT_LINES;
	int len;

        if (argc > 2) {
                printf("Usage: ./tail -n\n");
                return EXIT_FAILURE;
        }
	
	if (argc == 2) {
		if (argv[1][0] == '-' && isdigit(argv[1][1])) {
			char *end;
			n = strtoui(++argv[1], &end);
                        printf("%u\n", n);
			if (n == 0)
				return EXIT_FAILURE;
                }
		else  {
			printf("Usage: ./tail -n\n");
			return EXIT_FAILURE;
		}
	}
       	
	char *nlineptr[n];
	static char line[_BUF_SIZE];

	for (int i = 0; i < n; i++)
		nlineptr[i] = NULL;
	int i = 0;

	while ((len = get_line(line, _BUF_SIZE)) >= 0) {
		if (i >= n)
			i = 0;
		
		if (nlineptr[i] != NULL)
			free(nlineptr[i]);
		nlineptr[i] = malloc(sizeof(char) * len + 1);
		if (!nlineptr[i])
			return EXIT_FAILURE;
		
		strcpy(nlineptr[i], line);
                i++;
	};
	
	for (int start = i, j = 0; j < n; j++) { 
		int idx = (start + j) % n;	
		if (nlineptr[idx]) {
			printf("%s", nlineptr[idx]);
			free(nlineptr[idx]);
		}
        }

        return 0;
}

int get_line(char *restrict line, size_t n){
	if (line == NULL)
		return -1;
	
	int len = 0, c;
	while (len < n - 1 && (c = getchar()) != EOF) {
		line[len++] = c;
		if (c == '\n')
			break;
	}
	
	if (c == EOF && len == 0)
		return -1;

	line[len] = '\0';
	return len;
}

uint16_t strtoui(const char *restrict start, char **restrict end) {
        if (start == NULL || end == NULL)
                return 0;
        while (isspace(*start))
                start++;
        
        uint16_t p = 0;
	while (isdigit(*start) && *start != '\0') {
                p = 10 * p + (*start - '0');
                start++;
        }
	
	*end = (char*)start;	
        return p;
}
