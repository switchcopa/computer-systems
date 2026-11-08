
#include "yas-parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define YAS_INIT_SYM_CAP 64

// yas-parser.c (Robust token matching helpers and fixed Pass 2 instruction handlers)

static void emit_byte(uint8_t *buf, size_t buf_size, size_t *offset, uint8_t b)
{
    if (*offset < buf_size) {
        buf[*offset] = b;
    }
    (*offset)++;
}

static void emit_quad(uint8_t *buf, size_t buf_size, size_t *offset, uint64_t val)
{
    for (int i = 0; i < 8; i++) {
        emit_byte(buf, buf_size, offset, (uint8_t)(val >> (i * 8)));
    }
}

static bool match_token(yas_parser *parser, token_type type)
{
    if (parser->tok_idx < parser->lexer->ntokens && 
        parser->lexer->tokens[parser->tok_idx].type == type) {
        parser->tok_idx++;
        return true;
    }
    return false;
}

static token *current_token(yas_parser *parser)
{
    if (parser->tok_idx < parser->lexer->ntokens) {
        return &parser->lexer->tokens[parser->tok_idx];
    }
    return NULL;
}

// Updated Pass 2 instruction decoding switch
// (Replace the manual tok_idx++ sequences inside yas_parse_pass2 with these robust checks)

static instruction_type get_instruction_type(const char *name)
{
    if (strcmp(name, "halt") == 0) return INS_HALT;
    if (strcmp(name, "nop") == 0) return INS_NOP;
    if (strcmp(name, "rrmovq") == 0) return INS_RRMOVQ;
    if (strcmp(name, "irmovq") == 0) return INS_IRMOVQ;
    if (strcmp(name, "rmmovq") == 0) return INS_RMMOVQ;
    if (strcmp(name, "mrmovq") == 0) return INS_MRMOVQ;
    if (strcmp(name, "addq") == 0 || strcmp(name, "subq") == 0 || 
        strcmp(name, "andq") == 0 || strcmp(name, "xorq") == 0) return INS_OPQ;
    if (name[0] == 'j' && name[1] != '\0') return INS_JXX;
    if (strcmp(name, "call") == 0) return INS_CALL;
    if (strcmp(name, "ret") == 0) return INS_RET;
    if (strcmp(name, "pushq") == 0) return INS_PUSHQ;
    if (strcmp(name, "popq") == 0) return INS_POPQ;
    return INS_UNKNOWN_INS;
}

static uint8_t get_register_id(const char *name)
{
    if (strcmp(name, "rax") == 0) return 0x0;
    if (strcmp(name, "rcx") == 0) return 0x1;
    if (strcmp(name, "rdx") == 0) return 0x2;
    if (strcmp(name, "rbx") == 0) return 0x3;
    if (strcmp(name, "rsp") == 0) return 0x4;
    if (strcmp(name, "rbp") == 0) return 0x5;
    if (strcmp(name, "rsi") == 0) return 0x6;
    if (strcmp(name, "rdi") == 0) return 0x7;
    if (strcmp(name, "r8") == 0)  return 0x8;
    if (strcmp(name, "r9") == 0)  return 0x9;
    if (strcmp(name, "r10") == 0) return 0xA;
    if (strcmp(name, "r11") == 0) return 0xB;
    if (strcmp(name, "r12") == 0) return 0xC;
    if (strcmp(name, "r13") == 0) return 0xD;
    if (strcmp(name, "r14") == 0) return 0xE;
    return 0xF; // None / invalid
}

static uint8_t get_instruction_size(instruction_type ins)
{
    switch (ins) {
        case INS_HALT:
        case INS_NOP:
        case INS_RET:
            return 1;
        case INS_RRMOVQ:
        case INS_OPQ:
        case INS_PUSHQ:
        case INS_POPQ:
            return 2;
        case INS_JXX:
        case INS_CALL:
            return 9;
        case INS_IRMOVQ:
        case INS_RMMOVQ:
        case INS_MRMOVQ:
            return 10;
        default:
            return 0;
    }
}

static void symbol_table_init(symbol_table_t *symtab)
{
    symtab->symbols = NULL;
    symtab->count = 0;
    symtab->capacity = 0;
}

static void symbol_table_free(symbol_table_t *symtab)
{
    for (size_t i = 0; i < symtab->count; i++) {
        free(symtab->symbols[i].name);
    }
    free(symtab->symbols);
}

static bool symbol_table_add(symbol_table_t *symtab, const char *name, uint64_t addr)
{
    if (symtab->count >= symtab->capacity) {
        size_t new_cap = symtab->capacity == 0 ? YAS_INIT_SYM_CAP : symtab->capacity * 2;
        symbol_t *new_syms = realloc(symtab->symbols, new_cap * sizeof(symbol_t));
        if (!new_syms) return false;
        symtab->symbols = new_syms;
        symtab->capacity = new_cap;
    }
    symtab->symbols[symtab->count].name = strdup(name);
    if (!symtab->symbols[symtab->count].name) return false;
    symtab->symbols[symtab->count].addr = addr;
    symtab->count++;
    return true;
}

uint64_t symbol_table_lookup(const symbol_table_t *symtab, const char *name)
{
    for (size_t i = 0; i < symtab->count; i++) {
        if (strcmp(symtab->symbols[i].name, name) == 0) {
            return symtab->symbols[i].addr;
        }
    }
    return UINT64_MAX;
}

void yas_parser_init(yas_parser *parser, yas_lexer *lexer)
{
    parser->lexer = lexer;
    parser->tok_idx = 0;
    symbol_table_init(&parser->symtab);
    parser->pc = 0;
    parser->error = false;
}

void yas_parser_free(yas_parser *parser)
{
    symbol_table_free(&parser->symtab);
}

// yas-parser.c (Updated Pass 1 with robust instruction and operand skipping)

bool yas_parse_pass2(yas_parser *parser, uint8_t *code_buf, size_t buf_size, size_t *out_size)
{
    parser->tok_idx = 0;
    parser->pc = 0;
    size_t emit_offset = 0;

    while (parser->tok_idx < parser->lexer->ntokens && !parser->error) {
        token *tok = current_token(parser);
        if (!tok) break;

        // Skip labels
        if (tok->type == TOKEN_IDENTIFER && parser->tok_idx + 1 < parser->lexer->ntokens) {
            if (parser->lexer->tokens[parser->tok_idx + 1].type == TOKEN_COLUMN) {
                parser->tok_idx += 2;
                continue;
            }
        }

        // Handle directives
        if (tok->type == TOKEN_DOT) {
            parser->tok_idx++;
            token *dir_tok = current_token(parser);
            if (dir_tok && dir_tok->type == TOKEN_IDENTIFER && dir_tok->payload.ident) {
                if (strcmp(dir_tok->payload.ident, "pos") == 0) {
                    parser->tok_idx++;
                    token *val_tok = current_token(parser);
                    if (val_tok && val_tok->type == TOKEN_INTEGER) {
                        parser->pc = val_tok->payload.cst_int;
                        emit_offset = parser->pc;
                        parser->tok_idx++;
                        continue;
                    }
                } else if (strcmp(dir_tok->payload.ident, "quad") == 0) {
                    parser->tok_idx++;
                    token *v_tok = current_token(parser);
                    uint64_t val = 0;
                    if (v_tok) {
                        if (v_tok->type == TOKEN_INTEGER) {
                            val = v_tok->payload.cst_int;
                            parser->tok_idx++;
                        } else if (v_tok->type == TOKEN_IDENTIFER && v_tok->payload.ident) {
                            val = symbol_table_lookup(&parser->symtab, v_tok->payload.ident);
                            parser->tok_idx++;
                        }
                    }
                    emit_quad(code_buf, buf_size, &emit_offset, val);
                    parser->pc += 8;
                    continue;
                }
            }
        }

        // Handle instructions
        if (tok->type == TOKEN_IDENTIFER && tok->payload.ident) {
            const char *mnemonic = tok->payload.ident;
            instruction_type ins = get_instruction_type(mnemonic);

            if (ins == INS_HALT) {
                emit_byte(code_buf, buf_size, &emit_offset, 0x00);
                parser->pc += 1;
                parser->tok_idx++;
                continue;
            }
            if (ins == INS_NOP) {
                emit_byte(code_buf, buf_size, &emit_offset, 0x10);
                parser->pc += 1;
                parser->tok_idx++;
                continue;
            }
            if (ins == INS_RET) {
                emit_byte(code_buf, buf_size, &emit_offset, 0x90);
                parser->pc += 1;
                parser->tok_idx++;
                continue;
            }

            // RRMOVQ / OPQ
            if (ins == INS_RRMOVQ || ins == INS_OPQ) {
                uint8_t icode = (ins == INS_RRMOVQ) ? 0x2 : 0x6;
                uint8_t ifun = 0x0;
                if (strcmp(mnemonic, "rrmovq") == 0) ifun = 0x0;
                else if (strcmp(mnemonic, "addq") == 0) ifun = 0x0;
                else if (strcmp(mnemonic, "subq") == 0) ifun = 0x1;
                else if (strcmp(mnemonic, "andq") == 0) ifun = 0x2;
                else if (strcmp(mnemonic, "xorq") == 0) ifun = 0x3;

                parser->tok_idx++;
                
                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rA_tok = current_token(parser);
                uint8_t rA = (rA_tok && rA_tok->payload.ident) ? get_register_id(rA_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rB_tok = current_token(parser);
                uint8_t rB = (rB_tok && rB_tok->payload.ident) ? get_register_id(rB_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, (icode << 4) | ifun);
                emit_byte(code_buf, buf_size, &emit_offset, (rA << 4) | rB);
                parser->pc += 2;
                continue;
            }

            // IRMOVQ
            if (ins == INS_IRMOVQ) {
                parser->tok_idx++;
                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_INTEGER) {
                    parser->tok_idx++;
                }
                token *val_tok = current_token(parser);
                uint64_t val = val_tok ? val_tok->payload.cst_int : 0;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rB_tok = current_token(parser);
                uint8_t rB = (rB_tok && rB_tok->payload.ident) ? get_register_id(rB_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, 0x30);
                emit_byte(code_buf, buf_size, &emit_offset, (0xF << 4) | rB);
                emit_quad(code_buf, buf_size, &emit_offset, val);
                parser->pc += 10;
                continue;
            }

            // PUSHQ / POPQ
            if (ins == INS_PUSHQ || ins == INS_POPQ) {
                uint8_t icode = (ins == INS_PUSHQ) ? 0xA : 0xB;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rA_tok = current_token(parser);
                uint8_t rA = (rA_tok && rA_tok->payload.ident) ? get_register_id(rA_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, (icode << 4) | 0x0);
                emit_byte(code_buf, buf_size, &emit_offset, (rA << 4) | 0xF);
                parser->pc += 2;
                continue;
            }

            // CALL / JXX
            if (ins == INS_CALL || ins == INS_JXX) {
                uint8_t icode = (ins == INS_CALL) ? 0x8 : 0x7;
                uint8_t ifun = 0x0;
                if (ins == INS_JXX) {
                    if (strcmp(mnemonic, "jmp") == 0) ifun = 0x0;
                    else if (strcmp(mnemonic, "jle") == 0) ifun = 0x1;
                    else if (strcmp(mnemonic, "jl") == 0)  ifun = 0x2;
                    else if (strcmp(mnemonic, "je") == 0)  ifun = 0x3;
                    else if (strcmp(mnemonic, "jne") == 0) ifun = 0x4;
                    else if (strcmp(mnemonic, "jge") == 0) ifun = 0x5;
                    else if (strcmp(mnemonic, "jg") == 0)  ifun = 0x6;
                }

                parser->tok_idx++;
                token *dest_tok = current_token(parser);
                uint64_t dest = 0;
                if (dest_tok) {
                    if (dest_tok->type == TOKEN_INTEGER) {
                        dest = dest_tok->payload.cst_int;
                    } else if (dest_tok->type == TOKEN_IDENTIFER && dest_tok->payload.ident) {
                        dest = symbol_table_lookup(&parser->symtab, dest_tok->payload.ident);
                    }
                }
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, (icode << 4) | ifun);
                emit_quad(code_buf, buf_size, &emit_offset, dest);
                parser->pc += 9;
                continue;
            }

            // RMMOVQ
            if (ins == INS_RMMOVQ) {
                parser->tok_idx++;
                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rA_tok = current_token(parser);
                uint8_t rA = (rA_tok && rA_tok->payload.ident) ? get_register_id(rA_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_INTEGER) {
                    parser->tok_idx++;
                }
                token *disp_tok = current_token(parser);
                uint64_t disp = disp_tok ? disp_tok->payload.cst_int : 0;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rB_tok = current_token(parser);
                uint8_t rB = (rB_tok && rB_tok->payload.ident) ? get_register_id(rB_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, 0x40);
                emit_byte(code_buf, buf_size, &emit_offset, (rA << 4) | rB);
                emit_quad(code_buf, buf_size, &emit_offset, disp);
                parser->pc += 10;
                continue;
            }

            // MRMOVQ
            if (ins == INS_MRMOVQ) {
                parser->tok_idx++;
                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_INTEGER) {
                    parser->tok_idx++;
                }
                token *disp_tok = current_token(parser);
                uint64_t disp = disp_tok ? disp_tok->payload.cst_int : 0;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rB_tok = current_token(parser);
                uint8_t rB = (rB_tok && rB_tok->payload.ident) ? get_register_id(rB_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                while (parser->tok_idx < parser->lexer->ntokens && 
                       parser->lexer->tokens[parser->tok_idx].type != TOKEN_IDENTIFER) {
                    parser->tok_idx++;
                }
                token *rA_tok = current_token(parser);
                uint8_t rA = (rA_tok && rA_tok->payload.ident) ? get_register_id(rA_tok->payload.ident) : 0xF;
                parser->tok_idx++;

                emit_byte(code_buf, buf_size, &emit_offset, 0x50);
                emit_byte(code_buf, buf_size, &emit_offset, (rA << 4) | rB);
                emit_quad(code_buf, buf_size, &emit_offset, disp);
                parser->pc += 10;
                continue;
            }
        }

        parser->tok_idx++;
    }

    *out_size = emit_offset;
    return !parser->error;
}

static bool is_instruction_mnemonic(const char *name)
{
    return get_instruction_type(name) != INS_UNKNOWN_INS;
}

bool yas_parse_pass1(yas_parser *parser)
{
    parser->tok_idx = 0;
    parser->pc = 0;

    while (parser->tok_idx < parser->lexer->ntokens && !parser->error) {
        token *tok = current_token(parser);
        if (!tok) break;

        // 1. Label definition
        if (tok->type == TOKEN_IDENTIFER && parser->tok_idx + 1 < parser->lexer->ntokens) {
            token *next_tok = &parser->lexer->tokens[parser->tok_idx + 1];
            if (next_tok->type == TOKEN_COLUMN) {
                if (symbol_table_lookup(&parser->symtab, tok->payload.ident) != UINT64_MAX) {
                    fprintf(stderr, "Error: Duplicate label '%s'\n", tok->payload.ident);
                    parser->error = true;
                    break;
                }
                if (!symbol_table_add(&parser->symtab, tok->payload.ident, parser->pc)) {
                    parser->error = true;
                    break;
                }
                parser->tok_idx += 2;
                continue;
            }
        }

        // 2. Directives (.pos, .quad)
        if (tok->type == TOKEN_DOT) {
            parser->tok_idx++;
            token *dir_tok = current_token(parser);
            if (dir_tok && dir_tok->type == TOKEN_IDENTIFER && dir_tok->payload.ident) {
                if (strcmp(dir_tok->payload.ident, "pos") == 0) {
                    parser->tok_idx++;
                    token *val_tok = current_token(parser);
                    if (val_tok && val_tok->type == TOKEN_INTEGER) {
                        parser->pc = val_tok->payload.cst_int;
                        parser->tok_idx++;
                        continue;
                    }
                } else if (strcmp(dir_tok->payload.ident, "quad") == 0) {
                    parser->pc += 8;
                    parser->tok_idx++;
                    while (parser->tok_idx < parser->lexer->ntokens) {
                        token *t = current_token(parser);
                        if (!t || t->type == TOKEN_DOT || t->type == TOKEN_COLUMN) break;
                        if (t->type == TOKEN_IDENTIFER && t->payload.ident && 
                            (is_instruction_mnemonic(t->payload.ident) || 
                            (parser->tok_idx + 1 < parser->lexer->ntokens && parser->lexer->tokens[parser->tok_idx + 1].type == TOKEN_COLUMN))) {
                            break;
                        }
                        parser->tok_idx++;
                    }
                    continue;
                }
            }
        }

        // 3. Instructions
        if (tok->type == TOKEN_IDENTIFER && tok->payload.ident) {
            instruction_type ins = get_instruction_type(tok->payload.ident);
            uint8_t size = get_instruction_size(ins);
            if (size > 0) {
                parser->pc += size;
                parser->tok_idx++;
                
                while (parser->tok_idx < parser->lexer->ntokens) {
                    token *t = current_token(parser);
                    if (!t || t->type == TOKEN_DOT) break;
                    if (t->type == TOKEN_IDENTIFER && t->payload.ident) {
                        if (is_instruction_mnemonic(t->payload.ident)) break;
                        if (parser->tok_idx + 1 < parser->lexer->ntokens && 
                            parser->lexer->tokens[parser->tok_idx + 1].type == TOKEN_COLUMN) break;
                    }
                    parser->tok_idx++;
                }
                continue;
            }
        }

        parser->tok_idx++;
    }

    return !parser->error;
}
