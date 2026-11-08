
#include "yas-lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define YAS_INIT_TOKEN_CAP 500

typedef token *(*token_handler)(yas_lexer *);

static token *yas_token_alloc(yas_lexer *lexer);
static char yas_lexer_advance(yas_lexer *lexer);
static void yas_lexer_skip_whitespace(yas_lexer *lexer);
static location_t yas_get_location(yas_lexer *lexer);

static token *yas_handle_char(yas_lexer *lexer);
static token *yas_handle_comment(yas_lexer *lexer);
static token *yas_handle_integer(yas_lexer *lexer);
static token *yas_handle_ident(yas_lexer *lexer);
static token *yas_handle_underscore(yas_lexer *lexer);
static token *yas_handle_unknown(yas_lexer *lexer);

static const token_handler handlers[TOKEN_NTYPES] = {
    [TOKEN_DOT]        = yas_handle_char,
    [TOKEN_MINUS]      = yas_handle_char,
    [TOKEN_LPAREN]     = yas_handle_char,
    [TOKEN_RPAREN]     = yas_handle_char,
    [TOKEN_COLUMN]     = yas_handle_char,
    [TOKEN_PERCENT]    = yas_handle_char,
    [TOKEN_INTEGER]    = yas_handle_integer,
    [TOKEN_HASHTAG]    = yas_handle_comment,
    [TOKEN_IDENTIFER]  = yas_handle_ident,
    [TOKEN_UNDERSCORE] = yas_handle_underscore,
    [TOKEN_UNKNOWN]    = yas_handle_unknown,
};

static const token_type types[256] = {
    [0 ... 255]     = TOKEN_UNKNOWN,
    ['.']           = TOKEN_DOT,
    ['-']           = TOKEN_MINUS,
    ['(']           = TOKEN_LPAREN,
    [')']           = TOKEN_RPAREN,
    [':']           = TOKEN_COLUMN,
    ['%']           = TOKEN_PERCENT,
    ['0' ... '9']   = TOKEN_INTEGER,
    ['#']           = TOKEN_HASHTAG,
    ['a' ... 'z']   = TOKEN_IDENTIFER,
    ['A' ... 'Z']   = TOKEN_IDENTIFER,
    ['_']           = TOKEN_UNDERSCORE
};

static bool is_ident_mid(char c)
{
    return __builtin_isalpha(c) ||
           __builtin_isalnum(c) ||
           (c == '_');
}

static char yas_lexer_advance(yas_lexer *lexer)
{
    char c = *lexer->curr;
    if (c == '\0') return '\0';
    lexer->curr++;
    if (c == '\n') {
        lexer->line++;
        lexer->col = 1;
    } else {
        lexer->col++;
    }
    return c;
}

static void yas_lexer_skip_whitespace(yas_lexer *lexer)
{
    while (*lexer->curr != '\0') {
        char c = *lexer->curr;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f') {
            yas_lexer_advance(lexer);
        } else {
            break;
        }
    }
}

static location_t yas_get_location(yas_lexer *lexer)
{
    return ((uint64_t)lexer->line << 32) | (lexer->col & 0xFFFFFFFF);
}

static token *yas_token_alloc(yas_lexer *lexer)
{
    if (lexer->ntokens >= lexer->capacity) {
        size_t new_cap = lexer->capacity == 0 ? YAS_INIT_TOKEN_CAP : lexer->capacity * 2;
        token *new_tokens = realloc(lexer->tokens, new_cap * sizeof(token));
        if (!new_tokens) {
            lexer->error = true;
            return nullptr;
        }
        lexer->tokens = new_tokens;
        lexer->capacity = new_cap;
    }

    token *tok = &lexer->tokens[lexer->ntokens++];
    tok->loc = yas_get_location(lexer);
    return tok;
}

static token *yas_handle_char(yas_lexer *lexer)
{
    token *tok = yas_token_alloc(lexer);
    if (!tok) return nullptr;
    tok->type = types[(unsigned char)*lexer->curr];
    yas_lexer_advance(lexer);
    return tok;
}

static token *yas_handle_underscore(yas_lexer *lexer)
{
    return yas_handle_ident(lexer);
}

static token *yas_handle_ident(yas_lexer *lexer)
{
    location_t start_loc = yas_get_location(lexer);
    char *beg = lexer->curr;
    char *p = beg;
    while (*p != '\0' && is_ident_mid(*p)) {
        p++;
    }
    size_t len = p - beg;
    
    token *tok = yas_token_alloc(lexer);
    if (!tok) return nullptr;

    tok->type = TOKEN_IDENTIFER;
    tok->loc = start_loc;
    tok->payload.ident = strndup(beg, len);

    while (lexer->curr < p) {
        yas_lexer_advance(lexer);
    }
    return tok;
}

static token *yas_handle_integer(yas_lexer *lexer)
{
    location_t start_loc = yas_get_location(lexer);
    char *end;
    uint64_t val = strtoull(lexer->curr, &end, 0);

    token *tok = yas_token_alloc(lexer);
    if (!tok) return nullptr;

    tok->type = TOKEN_INTEGER;
    tok->loc = start_loc;
    tok->payload.cst_int = val;

    while (lexer->curr < end) {
        yas_lexer_advance(lexer);
    }
    return tok;
}

static token *yas_handle_comment(yas_lexer *lexer)
{
    while (*lexer->curr != '\0' && *lexer->curr != '\n') {
        yas_lexer_advance(lexer);
    }
    if (*lexer->curr == '\n') {
        yas_lexer_advance(lexer);
    }
    return nullptr;
}

static token *yas_handle_unknown(yas_lexer *lexer)
{
    yas_lexer_advance(lexer);
    return nullptr;
}

void yas_lex_init(yas_lexer *lexer, char *stream)
{
    lexer->stream = stream;
    lexer->curr = stream;
    lexer->tokens = nullptr;
    lexer->capacity = 0;
    lexer->ntokens = 0;
    lexer->line = 1;
    lexer->col = 1;
    lexer->error = false;
}

bool yas_lex_run(yas_lexer *lexer)
{
    while (*lexer->curr != '\0' && !lexer->error) {
        yas_lexer_skip_whitespace(lexer);
        if (*lexer->curr == '\0') break;

        char c = *lexer->curr;
        token_type t = types[(unsigned char)c];
        token_handler handler = handlers[t];
        if (handler) {
            handler(lexer);
        } else {
            yas_lexer_advance(lexer);
        }
    }
    return !lexer->error;
}
