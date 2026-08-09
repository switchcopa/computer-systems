#include <stdio.h>
#include <stdlib.h>

/* entab: replace n spaces in input with '\t' 
 * character
 */

#define DEFAULT_TAB_STOP 4
#define BUF_SIZE 1028

void entab(char *restrict dest, const char *restrict src, int tabstop);

int
main(int argc, char **argv)
{
	if (argc == 1 || argc > 3)
	{
		printf("Usage: ./entab \"String\" <n-tab-stops>\n");
		return EXIT_FAILURE;
	}

	const char *src = argv[1];
	if (src == NULL)
		return EXIT_FAILURE;
	
	int tabstops = DEFAULT_TAB_STOP;
	if (argc == 3)
		tabstops = atoi(argv[2]);
	char dest[BUF_SIZE];
	entab(dest, src, tabstops);
	printf("%s\n", dest);

	return EXIT_SUCCESS;
}

void 
entab(char *restrict dest, const char *restrict src, int tabstop)
{
	int i = 0, j = 0, k, nspaces;

	while (src[i] != '\0')
	{
		if (src[i] == ' ')
                {
                        nspaces = 0;
                        while (src[i] == ' ')
			{	
				i++;
                                nspaces++;
			}

                        int tabs = nspaces / tabstop; 
                        int spaces = nspaces % tabstop;


                        for (int t = 0; t < tabs; t++)
                                dest[j++] = '\t';
                        for (int s = 0; s < spaces; s++)
                                dest[j++] = ' ';
                } else
			dest[j++] = src[i++];
        };
		
	dest[j] = '\0';
}
