#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];

int readlines(char **restrict lineptr, int nlines);
void writelines(char **restrict lineptr, int nlines);

void q_sort(void **restrict lineptr, int left, int right, 
		int (*comp)(void *, void *)); 
int numcmp(const char *restrict, const char *restrict);
int reverse_numcmp(const char *restrict, const char *restrict);
void swap(void **restrict, int, int);
int get_line(char *restrict line, int maxlines);

int main(int argc, char **argv) {
	int nlines;
	int numeric = 0, reverse = 0;

	if ((argc > 1 && strcmp(argv[1], "-n") == 0) || (argc > 2 && strcmp(argv[2], "-n") == 0))
		numeric = 1;
	if ((argc > 1 && strcmp(argv[1], "-r") == 0) || (argc > 2 && strcmp(argv[2], "-r") == 0))
		reverse = 1;
        
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		q_sort((void**) lineptr, 0, nlines-1, 
			(int (*) (void *, void *)) (
			(numeric ? (reverse ? reverse_numcmp : numcmp) : strcmp)));
		writelines(lineptr, nlines);
		
		for (int i = 0; i < nlines; i++)
			free(lineptr[i]);	
		return 0;
	} else {
		printf("input too big to sort\n");	
		return 1;
	}
}

int readlines(char **restrict lineptr, int maxlines) {
	int len, nlines;
	char *p, line[maxlines];

	nlines = 0;
	while ((len = get_line(line, maxlines)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}

	return nlines;
}

void writelines(char **restrict lineptr, int nlines) {
	for (int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void q_sort(void **restrict lineptr, int left, int right, 
		int (*comp)(void *, void *)) {
	int i, last;

	void swap(void **lineptr, int, int);

	if (left >= right)
		return;	 
	swap(lineptr, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(lineptr[i], lineptr[left]) < 0)
			swap(lineptr, ++last, i);
	swap(lineptr, left, last);
	q_sort(lineptr, left, last-1, comp);
	q_sort(lineptr, last+1, right, comp);
}

int numcmp(const char *restrict s1, const char *restrict s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int reverse_numcmp(const char *restrict s1, const char *restrict s2) {
	double v1, v2;
	
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return 1;
	else if (v1 > v2)
		return -1;
	else return 0;
}

void swap(void **restrict v, int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int get_line(char *restrict line, int maxlines) {
	int len = 0, c;

	while (len < maxlines - 1 && (c = getchar()) != EOF) {
		line[len++] = c;
		if (c == '\n')
			break;
	}

	if (len == 0 && c == EOF)
		return -1;
	
	line[len] = '\0';
	return len;
}
