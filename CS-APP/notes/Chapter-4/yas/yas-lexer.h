
// yas-lexer.h
#ifndef YAS_LEXER_H
#define YAS_LEXER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint64_t location_t;

#define LOC_LINE(loc) ((uint32_t)((loc) >> 32))
#define LOC_COL(loc)  ((uint32_t)((loc) & 0xFFFFFFFF))

typedef enum {
    TOKEN_DOT,
    TOKEN_MINUS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COLUMN,
    TOKEN_PERCENT,
    TOKEN_INTEGER,
    TOKEN_HASHTAG,
    TOKEN_UNKNOWN,
    TOKEN_IDENTIFER,
    TOKEN_UNDERSCORE,
    TOKEN_NTYPES
} token_type;

typedef struct {
    token_type type;
    location_t loc;

    union payload {
        uint64_t cst_int;
        char *ident;
    } payload;
} token;

typedef struct {
    char *fn;
    char *curr;
    char *stream;

    token *tokens;
    size_t capacity;
    size_t ntokens;

    uint32_t line;
    uint32_t col;

    bool error;
} yas_lexer;

void yas_lex_init(yas_lexer *lexer, char *stream);
bool yas_lex_run(yas_lexer *lexer);

#endif
