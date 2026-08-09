#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD 100

struct key
{
    char *word;
    int count;
} keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    { "int", 0 },
    { "for", 0 },
    { "return", 0}, 
    { "signed", 0 },
    { "size_t", 0 },
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 }
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
static char stk[MAX_WORD];
static int sp = 0;

#define N_KEYS (int)(sizeof keytab / sizeof(struct key))

int main()
{
    int n;
    char word[MAX_WORD];

    while (getword(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, N_KEYS)) >= 0)
                keytab[n].count++;

    for (n = 0; n < N_KEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);

    char *w = word;
    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
}

int getch(void)
{
    return (sp > 0) ? stk[--sp] : getchar();
}

void ungetch(int c)
{
    if (sp >= MAX_WORD)
    {
        fprintf(stderr, "stack full\n");
        exit(EXIT_FAILURE);
    } else
        stk[sp++] = c;
}
