#ifndef _LEXER_H
#define _LEXER_H

#include <stdint.h>
#include <stddef.h>

#include <serror.h>

typedef enum
{
    TOK_PLUS = 0,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_INTLIT,
} token_type_t;

extern const char *TOKEN_NAMES[];

typedef struct
{
    token_type_t type;
    const char *text;
    size_t len;

    position_t start, end;
    
    uint64_t intval;
} token_t;

token_t *token_clone(token_t *tok);

// lex(NULL, NULL) to reset
token_t *lex(token_t *tok, const char *text);
token_t *peek(token_t *tok, const char *text);

#endif