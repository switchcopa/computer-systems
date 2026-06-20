#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

unsigned hash(const char *s);
struct nlist *lookup(const char *s);
char *strdup(const char *s);
struct nlist *install(const char *name, const char *defn);

bool undef(const char *name);
static void freenlist(struct nlist *p);

int main(void)
{
    return EXIT_SUCCESS;
}

unsigned hash(const char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(const char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

char *strdup(const char *s)
{
    size_t len = strlen(s);
    char *p = malloc(sizeof(char) * (len + 1));
    if (!p) return NULL;

    memcpy(p, s, len);
    p[len] = '\0';
    return p;
}

struct nlist *install(const char *name, const char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *)np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* undef: return true if name is in the hash table and delete it, else false*/
bool undef(const char *name)
{
    struct nlist *np;
    struct nlist *prev = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0) {
            struct nlist *p = hashtab[hashval];
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;
            freenlist(p);
            return true;
        }
        prev = np;
    }

    return false;
}

static void freenlist(struct nlist *p) {
    free(p->name);
    free(p->defn);
    free(p);
}
