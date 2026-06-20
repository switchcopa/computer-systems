#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int get_line(char *line, unsigned int max_size);

void swap(char *v[], int left, int right);
void q_sort(char *v[], int left, int right);

int main(void) {
        int nlines;
        int ret;

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
                q_sort(lineptr, 0, nlines-1);
                writelines(lineptr, nlines);
                ret = 0;
        } else {
                printf("error: failed to sort input\n");
                ret = 1;
        }

        while (nlines-- > 0)
                free(lineptr[nlines]);
        
        return ret;
}

int readlines(char *lineptr[], int maxlines) {
        int len, nlines;
        char *p, line[MAXLEN];
        
        nlines = 0;
        while ((len = get_line(line, MAXLEN)) > 0) 
                if (nlines >= maxlines || (p = malloc(len)) == NULL)
                        return -1;
                else {
                        line[len - 1] = '\0';
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                } 

        return nlines;
}

void writelines(char *lineptr[], int nlines) {
        while (nlines-- > 0)
                printf("%s\n", *lineptr++);
}

void q_sort(char *v[], int left, int right) {
        int i, last;
        
        if (left >= right)
                return;
        swap(v, left, (left + right) / 2); 
        last = left;
        
        for (i = left + 1; i <= right; i++)
                if (strcmp(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        q_sort(v, left, last-1);
        q_sort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
        char *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

int get_line(char *line, unsigned int max_size) {
        int len, c;

        len = 0;
        while (--max_size > 0 && (c = getchar()) != EOF && c != '\n') 
                line[len++] = c;
        if (c == '\n')
                line[len++] = c;
        line[len] = '\0';
        return len;
}
