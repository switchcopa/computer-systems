#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 10
#define BUFSIZE 5000

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./print file1 file2 ...\n");
        exit(EXIT_FAILURE);
    }
    
    int nfiles = 1;
    char buf[BUFSIZE];
    while (nfiles < argc) {
        FILE *fp = fopen(argv[nfiles], "r");
        if (!fp) { fprintf(stderr, "failed to open file %s\n", argv[nfiles]); continue; }
        
        int lines = 1, page = 1;
        printf("\nFile: %s\t\t Page: %d\n\n", argv[nfiles], page);
        while (fgets(buf, BUFSIZE, fp)) {
            printf("%s", buf);
            if (lines++ > LINES_PER_PAGE) {
                printf("\fFile: %s\t\t Page: %d\n\n", argv[nfiles], ++page);
                lines = 1;
            }
        }

        nfiles++;
    }


    exit(EXIT_SUCCESS);
}
