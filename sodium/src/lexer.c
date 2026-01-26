#include <lexer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

const char *TOKEN_NAMES[] = {
    "TOK_PLUS",
    "TOK_MINUS",
    "TOK_MUL",
    "TOK_DIV",
    "TOK_LPAREN",
    "TOK_RPAREN",
    "TOK_INTLIT",
};

token_t *token_clone(token_t *tok)
{
    token_t *res = malloc(sizeof(token_t));
    memcpy(res, tok, sizeof(token_t));

    return res;
}

static token_t *match_token(token_t *tok, const char *text, size_t *idx)
{
    if (text[*idx] == '+')
    {
        tok->type = TOK_PLUS;
        tok->text = &text[*idx];
        tok->len = 1;

        (*idx)++;

        return tok;
    }
    else if (text[*idx] == '-')
    {
        tok->type = TOK_MINUS;
        tok->text = &text[*idx];
        tok->len = 1;
        
        (*idx)++;

        return tok;
    }
    else if (text[*idx] == '*')
    {
        tok->type = TOK_MUL;
        tok->text = &text[*idx];
        tok->len = 1;
        
        (*idx)++;

        return tok;
    }
    else if (text[*idx] == '/')
    {
        tok->type = TOK_DIV;
        tok->text = &text[*idx];
        tok->len = 1;
        
        (*idx)++;

        return tok;
    }
    else if (text[*idx] == '(')
    {
        tok->type = TOK_LPAREN;
        tok->text = &text[*idx];
        tok->len = 1;
        
        (*idx)++;

        return tok;
    }
    else if (text[*idx] == ')')
    {
        tok->type = TOK_RPAREN;
        tok->text = &text[*idx];
        tok->len = 1;
        
        (*idx)++;

        return tok;
    }
    else if (isdigit(text[*idx]))
    {
        tok->type = TOK_INTLIT;
        tok->text = &text[*idx];

        tok->intval = 0;
        tok->len = 0;
        while (isdigit(text[*idx]))
        {
            tok->intval *= 10;
            tok->intval += text[(*idx)++] - '0';

            tok->len++;
        }

        return tok;
    }

    fprintf(stderr, "unknown token\n");
    return NULL;
}

static size_t lex_index = 0;

token_t *lex(token_t *tok, const char *text)
{
    if (!text)
    {
        lex_index = 0;
        return NULL;
    }

    assert(tok);
    assert(text);

    if (!text[lex_index])
    {
        return NULL;
    }

    return match_token(tok, text, &lex_index);
}

token_t *peek(token_t *tok, const char *text)
{
    assert(tok);
    assert(text);

    if (!text[lex_index])
    {
        return NULL;
    }

    size_t idx = lex_index;
    return match_token(tok, text, &idx);
}
