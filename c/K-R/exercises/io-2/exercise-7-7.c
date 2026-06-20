#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 8024

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./grep \"pattern\" file1 file2 ...\n");
        exit(EXIT_FAILURE);
    }
    
    int mode; 
    if (argc == 2)
        mode = 1;
    else mode = 0;

    const char *pattern = argv[1];
    int nfiles = 2;

    int mstrstr(const char *haystack, const char *needle);
    int getline(char *dest, int max, FILE *fsrc);

    char line[BUFSIZE];
    while (mode || nfiles < argc) {
        FILE *fp = !mode ? fopen(argv[nfiles], "r") : stdin;
        if (!fp) { fprintf(stderr, "failed to open %s\n", argv[nfiles++]); continue; }
        while (getline(line, BUFSIZE, fp))
            if (mstrstr(line, pattern))
                printf("%s: %s", !mode ? argv[nfiles] : "stdin", line);
        if (mode) break;

        fclose(fp);
        nfiles++;
    }
}

int mstrstr(const char *haystack, const char *needle) {
    for (int i = 0; haystack[i] != '\0'; i++) {
        int j, k;
        for (j = 0, k = i; haystack[k] == needle[j]; k++, j++)
            ;
        if (needle[j] == '\0')
            return 1;
    }

    return 0;
}

int getline(char *dest, int max, FILE *fsrc) {
    if (fgets(dest, max, fsrc) == NULL)
        return 0;
    else return strlen(dest);
}
