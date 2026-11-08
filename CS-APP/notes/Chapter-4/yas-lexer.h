
#ifndef YAS_LEXER_H
#define YAS_LEXER_H

#include <stdint.h>

typedef uint64_t location_t;

enum token_type {
    TOKEN_DOT,
    TOKEN_MINUS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COLUMN,
    TOKEN_PERCENT,
    TOKEN_INTEGER,
    TOKEN_HASHTAG,
    TOKEN_IDENTIFER,
};

typedef struct {
    enum token_type type;

    union payload {
        uint64_t cst_int;
        char *ident;
    };
} token;

typedef struct {
    char *stream;
    token *tokens;
    location_t ntokens;
} lexer;

#endif
