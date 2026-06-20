#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "reader.h"
#include "tnode.h"

static const char *noise[] = {
	"a","an","and","are","as","at","be","but","by","for","from","had","has","have",
	"he","her","him","his","i","in","is","it","its","of","on","or","that","the",
	"to","was","were","with","you"
};

static int noise_binsearch(const char *word);
static char *getword(const char * restrict src, int *bufp);
static void treeprint(struct tnode *tree);

int main(void)
{
    struct tnode *tree = NULL;
    struct input_reader ir;
    if (read_input(&ir) < 0) {
        fprintf(stderr, "failed to read input\n");
        return EXIT_FAILURE;
    }

    int line = 0;
    while (ir.bufp < ir.buflen - 1) {
        char *word = getword(ir.buffer, &ir.bufp);
        if (!word) {
            fprintf(stderr, "failed to allocate memory for word\n");
            return EXIT_FAILURE;
        }

        if (word[0] != '\0' && !noise_binsearch(word))
            tree = tree_add(tree, word, line);
        free(word);
    }

    treeprint(tree);
    tfree(tree);
}

static int noise_binsearch(const char *word)
{
    int left = 0;
    int right = sizeof(noise) / sizeof(noise[0]) - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        int cmp = strcmp(word, noise[middle]);

        if (cmp == 0)
            return 1;
        if (cmp < 0)
            right = middle - 1;
        else
            left = middle + 1;
    }

    return 0;
}

static char *getword(const char * restrict src, int *bufp)
{
    char *buf = malloc(sizeof(char) * (WORD_SIZE + 1));
    if (!buf) return NULL;
   
    while (src[*bufp] != '\0' && !isalnum((unsigned char)src[*bufp++]));
    
    if (src[*bufp] == '\0')
    {
        buf[0] = '\0';
        return buf;
    }

    int i = 0;
    while(i < WORD_SIZE - 1 && src[*bufp] != '\0' &&
         isalnum((unsigned char)src[*bufp]))
        buf[i++] = src[*bufp++];

    buf[i] = '\0';
    return buf;
}

static void treeprint(struct tnode *tree)
{
    if (!tree) return;

    treeprint(tree->left);
    printf("%s: ", tree->word);
    for (int i = 0; i < tree->linesp; i++)
        printf("%d ", tree->lines[i]);
    printf("\n");

    treeprint(tree->right);
}