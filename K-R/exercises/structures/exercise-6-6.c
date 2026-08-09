#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>

#define HASHSIZE    101
#define BUFSIZE     256
#define FBUFSIZE    1000000
#define WORD_SIZE   32
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

// utils
char *loadfile(const char *filename, ssize_t *size);
void appendbuf(char *buf, int *i, int c);

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./app \"filename.c\"\n");
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    ssize_t size = 0;
    char *fbuf = loadfile(filename, &size);
    if (!fbuf)
        goto allocerr;

    enum {
        NORMAL,
        COMMENT,
        MCOMMENT,
        STRING,
        CHAR,
    } state = NORMAL;

    int c, prev = 0;
    for (int i = 0; i < size && (c = fbuf[i]); i++)
    {
        switch (state) {

            case NORMAL:
                if (prev == '/') {
                    if (c == '/') { state = COMMENT; prev = 0; continue; }
                    else if (c == '*') { state = MCOMMENT; prev = 0; continue; }
                }
                else if (prev == '#') {
                    // handle preprocessor directive
                    // skip whitespace
                    while (i < size && (c = fbuf[i]) && (c == ' ' || c == '\t')) i++;
                    int start = i;
                    while (i < size && (c = fbuf[i]) && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) i++;
                    char directive[16];
                    int len = i - start;
                    strncpy(directive, fbuf + start, len);
                    directive[len] = '\0';

                    if (strcmp(directive, "define") == 0) {
                        // read name
                        while (i < size && (c = fbuf[i]) && (c == ' ' || c == '\t')) i++;
                        int nstart = i;
                        while (i < size && (c = fbuf[i]) && 
                            ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'))
                            i++;
                        int nlen = i - nstart;
                        char name[WORD_SIZE];
                        strncpy(name, fbuf + nstart, nlen);
                        name[nlen] = '\0';

                        // skip whitespace
                        while (i < size && (c = fbuf[i]) && (c == ' ' || c == '\t')) i++;

                        // read replacement until newline
                        int rstart = i;
                        while (i < size && (c = fbuf[i]) && c != '\n') i++;
                        int rlen = i - rstart;
                        char defn[BUFSIZE];
                        strncpy(defn, fbuf + rstart, rlen);
                        defn[rlen] = '\0';

                        install(name, defn);

                        prev = 0; // reset
                        continue;
                    } 
                    else if (strcmp(directive, "undef") == 0) {
                        // read name
                        while (i < size && (c = fbuf[i]) && (c == ' ' || c == '\t')) i++;
                        int nstart = i;
                        while (i < size && (c = fbuf[i]) && 
                            ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'))
                            i++;
                        int nlen = i - nstart;
                        char name[WORD_SIZE];
                        strncpy(name, fbuf + nstart, nlen);
                        name[nlen] = '\0';

                        undef(name);

                        prev = 0;
                        continue;
                    }
                    prev = 0;
                }

                // normal token processing
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                    int start = i;
                    while (i < size && (c = fbuf[i]) &&
                        ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
                            (c >= '0' && c <= '9') || c == '_')) i++;
                    int len = i - start;
                    char token[WORD_SIZE];
                    strncpy(token, fbuf + start, len);
                    token[len] = '\0';

                    struct nlist *np = lookup(token);
                    if (np)
                        printf("%s", np->defn); // replace
                    else
                        printf("%s", token);

                    i--; // adjust for for-loop increment
                }
                else {
                    putchar(c);
                }

                if (c == '/') prev = '/';
                else if (c == '#') prev = '#';
                else prev = 0;

                break;

            case COMMENT:
                if (c == '\n') state = NORMAL;
                putchar(c);
                break;

            case MCOMMENT:
                if (prev == '*' && c == '/') state = NORMAL;
                prev = c;
                putchar(c);
                break;

            case STRING:
                putchar(c);
                if (c == '"' && prev != '\\') state = NORMAL;
                prev = c;
                break;

            case CHAR:
                putchar(c);
                if (c == '\'' && prev != '\\') state = NORMAL;
                prev = c;
                break;
    }
    return EXIT_SUCCESS;
}
allocerr:
    fprintf(stderr, "allocation failure\n");
    return EXIT_FAILURE;
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

char *loadfile(const char *filename, ssize_t *outsize)
{
    FILE *fp = fopen(filename, "r");
    char *fbuffer = malloc(sizeof(char) * (FBUFSIZE + 1));
    if (!fp || !fbuffer) goto err;

    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    size_t n = fread(fbuffer, sizeof (char), fsize, fp);
    if (n < fsize && ferror(fp)) goto err;

    fbuffer[fsize] = '\0';
    fclose(fp);

    *outsize = fsize;
    return fbuffer;
err:
    if (!fp)
        return NULL;

    fclose(fp);
    *outsize = -1;
    return NULL;
}
