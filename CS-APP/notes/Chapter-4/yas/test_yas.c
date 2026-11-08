
// test_yas.c
#include "yas-lexer.h"
#include "yas-parser.h"
#include <stdio.h>
#include <stdlib.h>

extern bool yas_parse_pass1(yas_parser *parser);
extern bool yas_parse_pass2(yas_parser *parser, uint8_t *code_buf, size_t buf_size, size_t *out_size);

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *source = malloc(size + 1);
    if (!source) {
        fclose(f);
        return 1;
    }

    fread(source, 1, size, f);
    source[size] = '\0';
    fclose(f);

    yas_lexer lexer;
    yas_lex_init(&lexer, source);
    if (!yas_lex_run(&lexer)) {
        fprintf(stderr, "Lexing failed.\n");
        free(source);
        free(lexer.tokens);
        return 1;
    }

    yas_parser parser;
    yas_parser_init(&parser, &lexer);

    if (!yas_parse_pass1(&parser)) {
        fprintf(stderr, "Pass 1 failed.\n");
        yas_parser_free(&parser);
        free(source);
        free(lexer.tokens);
        return 1;
    }

    printf("--- Symbol Table ---\n");
    for (size_t i = 0; i < parser.symtab.count; i++) {
        printf("%s: 0x%lx\n", parser.symtab.symbols[i].name, parser.symtab.symbols[i].addr);
    }

    uint8_t code_buf[4096] = {0};
    size_t code_size = 0;

    if (!yas_parse_pass2(&parser, code_buf, sizeof(code_buf), &code_size)) {
        fprintf(stderr, "Pass 2 failed.\n");
        yas_parser_free(&parser);
        free(source);
        free(lexer.tokens);
        return 1;
    }

    printf("\n--- Emitted Machine Code (%zu bytes) ---\n", code_size);
    for (size_t i = 0; i < code_size; i++) {
        printf("%02x ", code_buf[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");

    FILE *bin_out = fopen("output.bin", "wb");
    if (bin_out) {
        fwrite(code_buf, 1, code_size, bin_out);
        fclose(bin_out);
        printf("\nSuccessfully emitted %zu bytes to 'output.bin'\n", code_size);
    } else {
        perror("Failed to open output binary file");
    }

    yas_parser_free(&parser);
    free(source);
    free(lexer.tokens);
    return 0;
}
