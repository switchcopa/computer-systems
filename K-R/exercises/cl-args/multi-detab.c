#include <stdio.h>
#include <stdlib.h>

/* multi-dentab: converts a list of '\t' by the user arguments as 
 * tab stops.
 */

#define DEFAULT_TAB_STOP 4
#define BUF_SIZE 1024

void mentab(char *restrict dest, const char *restrict src, int *restrict tab_stops, int n_tabs);

int
main(int argc, char **argv)
{
	if (argc == 1) 
	{
		printf("Usage: ./mdentab \"Hello\\tWorld\" <tab-list (optional)>\n");
		return EXIT_FAILURE;
	}

	const char *src = argv[1];
	int tab_stops[256];
	if (src == NULL)
		return EXIT_FAILURE;
	
	int ntabs = 0;
	for (int i = 0; i < argc - 2; i++, ntabs++)
		tab_stops[i] = atoi(argv[i+2]);

	char destbuf[BUF_SIZE];
	mentab(destbuf, src, tab_stops, ntabs);

	printf("%s\n", destbuf);
	return 0;
}

void
mentab(char *restrict dest, const char *restrict src, int *tab_stops, int n_tabs)
{
	int i = 0, j = 0, col = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\\' && src[i+1] == 't')
		{	
			if (col < n_tabs)
			{
				for (int k = 0; k < tab_stops[col]; k++)
					dest[j++] = ' ';
				col++;
				i += 2;
				continue;
			}

			for (int k = 0; k < DEFAULT_TAB_STOP; k++)
				dest[j++] = ' ';
			i += 2;
			continue;
		}

		dest[j++] = src[i++];
	}

	dest[j] = '\0';
}
