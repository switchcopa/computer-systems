#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1000

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./comp x.c y.c\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    if (!fp1 || !fp2) {
        printf("an error occurred while opening the files\n");
        exit(EXIT_FAILURE);
    }

    char line1[LINESIZE];
    char line2[LINESIZE];
    int line = 1;

    while (1) {
        char *p = fgets(line1, LINESIZE, fp1);
        char *q = fgets(line2, LINESIZE, fp2);
        if (!p && !q) {
            printf("files are the same\n");
            break;
        } else if (!p || !q)
            printf("Line: %d\n", line);

        if (strcmp(line1, line2) != 0) {
            printf("Line: %d\n", line);
            break;
        }

        line++;
    }

    fclose(fp1);
    fclose(fp2);
    exit(0);
}
