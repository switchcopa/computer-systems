#include <stdio.h>
#include <stdlib.h>

/* detab: converts a list of '\t' arguments as 
 * tab stops.
 */

#define DEFAULT_TAB_STOP 4
#define BUF_SIZE 1024

void entab(char *restrict, const char *restrict, int ntabs);

int
main(int argc, char **argv)
{
	if (argc == 1 || argc >= 4) 
	{
		printf("Usage: ./detab \"Hello\\tWorld\" <num-of-tabs (optional)>\n");
		return EXIT_FAILURE;
	}

	const char *src = argv[1];
	if (src == NULL)
		return EXIT_FAILURE;

	int ntabs;
	if (argc != 3)
		ntabs = -1;
	else
		ntabs = atoi(argv[2]);
	
	char strdest[BUF_SIZE];
	entab(strdest, src, ntabs);
	printf("%s\n", strdest);

	return 0;
}

void
entab(char *restrict dest, const char *restrict src, int ntabs)
{
	if (ntabs < 0)
		ntabs = DEFAULT_TAB_STOP;

	int i = 0, j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\\' && src[i+1] == 't')
		{
			for (int k = 0; k < ntabs; k++)
				dest[j++] = ' ';
			i += 2;
			continue;
		}

		dest[j++] = src[i++];
	}

	dest[j] = '\0';
}
