
// yas-parser.h
#ifndef YAS_PARSER_H
#define YAS_PARSER_H

#include "yas-lexer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    INS_HALT,
    INS_NOP,
    INS_RRMOVQ,
    INS_IRMOVQ,
    INS_RMMOVQ,
    INS_MRMOVQ,
    INS_OPQ,
    INS_JXX,
    INS_CALL,
    INS_RET,
    INS_PUSHQ,
    INS_POPQ,
    INS_UNKNOWN_INS
} instruction_type;

typedef struct {
    char *name;
    uint64_t addr;
} symbol_t;

typedef struct {
    symbol_t *symbols;
    size_t count;
    size_t capacity;
} symbol_table_t;

typedef struct {
    yas_lexer *lexer;
    size_t tok_idx;
    symbol_table_t symtab;
    uint64_t pc;
    bool error;
} yas_parser;

void yas_parser_init(yas_parser *parser, yas_lexer *lexer);
void yas_parser_free(yas_parser *parser);
bool yas_parse_pass1(yas_parser *parser);
bool yas_parse_pass2(yas_parser *parser, uint8_t *code_buf, size_t buf_size, size_t *out_size);

#endif
