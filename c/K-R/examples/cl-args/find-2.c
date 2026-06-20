#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

int get_line(char *line, int max);

/* find: print lines that match pattern rom 1st arg */
int main(int argc, char **argv) {
        char line[MAXLINE];
        long nline = 0;
        int c, except = 0, number = 0, found = 0;
        
        while (--argc > 0 && (*++argv)[0] == '-')
                while (c = *++argv[0])
                        switch (c) {
                                case 'x':
                                        except = 1;
                                        break;
                                case 'n':
                                        number = 1;
                                        break;
                                default:
                                        printf("find: illegal option %c\n", c);
                                        argc = 0;
                                        found = -1;
                                        break;
                        }

        if (argc != 1)
                printf("Usage: ./find -x -n pattern\n");
        else 
                while (get_line(line, MAXLINE) > 0) {
                        nline++;
                        if (strstr(line, *argv) != NULL) {
                                if (number)
                                        printf("%ld:", nline);
                                printf("%s", line);
                                found++;
                        }
                }

        return found;
}

int get_line(char *line, int max) {
        int c, i;
	
	i = 0;
	while (i < max - 1 && (c = getchar()) != EOF) {
		line[i++] = c;	

		if (c == '\n')
			break;
	}
	
	line[i] = '\0';
	return i;
}
