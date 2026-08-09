#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 128
#define TNODEPTR_ARR_SIZE 512
#define BUFFER_SIZE 8192

struct tnode
{
    char word[WORD_SIZE];
    struct tnode *left;
    struct tnode *right;
    int count;
};

struct tnode *talloc(const char *word);
struct tnode *tree_add(struct tnode *root, char *word);
void tree_to_array(struct tnode *root, struct tnode **arr, int *idx);
int cmp_freq_desc(const void *a, const void *b);
static void getword(char *dest, const char *src, int *p, int sup);

int main(void)
{
    char *buf = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf) { 
        fprintf(stderr, "failed to alloc memory for buffer\n");
        return EXIT_FAILURE;
    }
 
    int i = 0;
    int c;
    while ((c = getchar()) != EOF && i < BUFFER_SIZE - 1)
        buf[i++] = c;
    buf[i] = '\0';

    int bufp = 0;
    struct tnode *tree = NULL;
    while (buf[bufp] != '\0')
    {
        char word[WORD_SIZE];
        getword(word, buf, &bufp, WORD_SIZE);

        if (word[0] == '\0')
            continue;
        tree = tree_add(tree, word);
    }

    struct tnode **arr = malloc(sizeof(struct tnode *) * TNODEPTR_ARR_SIZE);
    if (!arr) {
        fprintf(stderr, "failed to alloc memory for tnode array\n");
        return EXIT_FAILURE;
    }

    int idx = 0;
    tree_to_array(tree, arr, &idx);
    qsort(arr, idx, sizeof(struct tnode *), cmp_freq_desc);

    for (int i = 0; i < idx; i++)
        printf("%d %s\n", arr[i]->count, arr[i]->word);

    return EXIT_SUCCESS;
}

struct tnode *talloc(const char *word)
{
    struct tnode *p = malloc(sizeof(struct tnode));
    if (!p) return NULL;

    strcpy(p->word, word);
    p->left = p->right = NULL;
    p->count = 1;
    return p;
}

struct tnode *tree_add(struct tnode *root, char *word)
{
    if (!root) {
        root = talloc(word);
        return root;
    }

    int cmp = strcmp(word, root->word);

    if (cmp == 0)
        root->count++;
    else if (cmp < 0)
        root->left = tree_add(root->left, word);
    else
        root->right = tree_add(root->right, word);

    return root;
}

void tree_to_array(struct tnode *root, struct tnode **arr, int *idx)
{
    if (!root) return;
    tree_to_array(root->left, arr, idx);
    arr[(*idx)++] = root;
    tree_to_array(root->right, arr, idx);
}

int cmp_freq_desc(const void *a, const void *b)
{
    const struct tnode *x = *(const struct tnode **)a;
    const struct tnode *y = *(const struct tnode **)b;

    return y->count - x->count;
}

static void getword(char *dest, const char *src, int *p, int sup)
{
    int i = 0;
    while (src[*p] && !isalnum((unsigned char) src[*p]))
        (*p)++;
    for (i = 0; src[*p] != '\0' && isalnum((unsigned char) src[*p]) && i < sup - 1; i++)
        dest[i] = src[(*p)++];

    dest[i] = '\0';
}
