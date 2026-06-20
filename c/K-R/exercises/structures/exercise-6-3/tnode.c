#include "tnode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tnode *talloc(const char *word)
{
    struct tnode *p = malloc(sizeof(struct tnode));
    if (!p) return NULL;

    strcpy(p->word, word);
    p->left = p->right = NULL;
    p->linesp = -1;
    return p;
}

struct tnode *tree_add(struct tnode *root, char *key, int line)
{
    if (!root) {
        root = talloc(key);
        tlines_add(root, line);
        return root;
    }
 
    int cmp = strcmp(root->word, key);
    if (cmp == 0) {
        tlines_add(root, line);
        return root;
    }
    else if (cmp < 0)
        root->left = tree_add(root->left, key, line);
    else
        root->right = tree_add(root->right, key, line);

    return root;
}

void tlines_add(struct tnode *p, int line)
{
    if (p->linesp >= 0 && p->linesp < MAX_LINES_APPEARANCE - 1)
        p->lines[++p->linesp] = line;
}

void tfree(struct tnode *p)
{
    if (!p) return;

    tfree(p->left);
    tfree(p->right);
    free(p);
}
