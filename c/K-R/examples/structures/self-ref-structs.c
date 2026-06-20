
/* there is a very important explanation on the libc function malloc(), which involves that the allocator
 * must return a pointer with the required alignment restrictions, and that most machines
 * require all objects in memory to guarantee a specific alignement rule. so make sure to check it out */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode
{
    char *word;
    struct tnode *left;
    struct tnode *right;
    int count;
};

#define MAX_WORD 100

char *strdup(char *);
struct tnode *talloc(void);

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main(void)
{
    struct tnode *root;
    char word[MAX_WORD];

    root = NULL;
    while (getword(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("\{%6s : %d\}\n", p->word, p->count);
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
    size_t len = strlen(s);
    char *p = (char *)malloc(len * sizeof(char));
    if (!p)
        return NULL;
    strcpy(p, s);
    return p;
}
