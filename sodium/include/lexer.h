#ifndef _LEXER_H
#define _LEXER_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    TOK_PLUS,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_INTLIT,
} token_type_t;

typedef struct
{
    token_type_t type;
    const char *text;
    size_t len;
    
    uint64_t intval;
} token_t;

// lex(NULL, NULL) to reset
token_t *lex(token_t *tok, const char *text);
token_t *peek(token_t *tok, const char *text);

#endif