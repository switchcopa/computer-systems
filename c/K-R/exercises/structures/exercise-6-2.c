
/*
Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set
from the command line.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_GROUP_SIZE   256
#define WORD_SIZE        32
#define DEFAULT_N_CHARS  6
#define FILE_BUFFER_SIZE 8192

struct tnode
{
    char *prefix;
    char **list_words;
    struct tnode *left;
    struct tnode *right;
};

enum
{
    NORMAL,
    QUOTE,
    DOUBLE_QUOTE,
    COMMENT,
    MCOMMENT,
} stinput;

struct tnode *talloc(char *w);
struct tnode *addtree(struct tnode *, char *);
int strprefix(const char * restrict, const char * restrict);

char *read_file(const char *filename);
void getword(char *dest, char *src, int *p);

static char input_buf[FILE_BUFFER_SIZE];
static char bufp = 0;
static uint64_t nchars = DEFAULT_N_CHARS;
char getch(void);
void ungetch(char);
void terminate(char *fbuf, struct tnode *p);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./cmp cfile.c\n");
        return -1;
    }

    struct tnode *root = NULL;
    return EXIT_SUCCESS;
}

struct tnode *talloc(char *w)
{
    if (!w)
        return NULL;
    struct tnode *p = malloc(sizeof(struct tnode));
    if (!p)
        return NULL;

    p->list_words = malloc(sizeof(char *) * MAX_GROUP_SIZE);
    if (!p->list_words)
    {
        free(p);
        return NULL;
    }

    for (int i = 0; i < MAX_GROUP_SIZE; i++)
        p->list_words[i] = NULL;
    p->prefix = malloc(sizeof(char) * (nchars + 1));
    if (!p->prefix)
    {
        free(p->list_words);
        free(p);
        return NULL;
    }
    strncpy(p->prefix, w, nchars);
    p->prefix[nchars] = '\0';
    p->list_words[0] = strdup(w);
    if (!p->list_words[0])
    {
        free(p->list_words[0]);
        free(p->prefix);
        free(p);
        return NULL;
    }

    p->left = p->right = NULL;
    return p;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    if (strlen(w) < nchars)
        return p;
    if (!p)
        return talloc(w);

    int cmp = strncmp(w, p->prefix, nchars);
    if (cmp == 0)
        for (int i = 0; i < MAX_GROUP_SIZE; i++)
        {
            if (p->list_words[i] == NULL)
            {
                p->list_words[i] = strdup(w);
                break;
            }

            if (strcmp(p->list_words[i], w) == 0)
                break;
        }
    else if (cmp < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

int strprefix(const char *restrict str, const char *restrict prefix)
{
    while (*prefix != '\0' && *str != '\0' && *str++ == *prefix++)
        ;

    if (*prefix == '\0')
        return 1;
    else return 0;
}

void read_file(const char *filename, char *buf)
{
    FILE *fp = fopen(filename, 'r');
    if (!fp)
        return;

    fseek(fp, 0, SEEK_END);
    size_t s = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int64_t bytes = fread(buf, sizeof(char), s, fp);
    if (bytes > 0 && bytes < FILE_BUFFER_SIZE - 1)
        buf[bytes++] = '\0';
    else
    fclose(fp);
}

void getword(char *dest, char *src, int *p)
{
    
    switch (stinput)
    {
        case NORMAL:
            int i;
            for (i = 0 ; i < WORD_SIZE - 1 && isalpha(src[*p]); i++)
                dest[i] = src[*p++];
            dest[i] = '\0';
            break;
        case QUOTE:
            while (src[*p++] != '\'')
                ; 
            break;
        case DOUBLE_QUOTE:
            while (src[*p++] != '\"')
                ;
            break;
        case COMMENT:
            while (src[*p++] != ' ')
                ;
            break;
        case MCOMMENT:
            while (src[*p] == '*' && src[*p + 1] == '/')
                *p += 2;
            break;
    }
}

void terminate(char *fbuf, struct tnode *p)
{
    if (!p || !fbuf)
    {
        free(fbuf);
        free(p);
        return;
    }

}

char getch(void)
{
    return (bufp > 0) ? input_buf[--bufp] : getchar();
}

void ungetch(char c)
{
    if (bufp >= FILE_BUFFER_SIZE)
    {
        fprintf(stderr, "attempt to push to full buffer\n");
        exit(EXIT_FAILURE);
    } else
        input_buf[bufp++] = c;
}
