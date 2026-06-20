#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
struct key *binsearch(char *, struct key *, int);
static char stk[MAX_WORD];
static int sp = 0;

int main(void)
{
    char word[MAX_WORD];
    struct key *p;

    while (getword(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            if ((p=binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;

    for (p = keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    return 0;
}

struct key *binsearch(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low  = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high)
    {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
                low = mid + 1;
        else
            return mid;
    }

    return NULL;
}
