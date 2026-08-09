#include <stdio.h>
#include <ctype.h>

int main(void) {
	int c, i;
	int digit_count[10];
	int blanks = 0, tabs = 0, newlines = 0, other = 0;
	
	for (i = 0; i < 10; i++)
		digit_count[i] = 0;
	
	while ((c = getchar()) != EOF) {
		if (isdigit(c))
			digit_count[c - '0']++;
		else if (c == '\t')
			tabs++;
		else if (c == ' ')
			blanks++;
		else if (c == '\n')
			newlines++;
		else
			other++;
	}

	printf("digits: ");
	for (i = 0; i < 10; i++)
		printf("%d ", digit_count[i]);
	printf("blanks: %d, tabs: %d, newlines: %d, other: %d\n", blanks, tabs, newlines, other);
	return 0;
}
