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

static uint64_t line, column;

#define CURRENT_POS(pos) \
    pos.line = line;     \
    pos.column = column; \
    pos.index = *idx;    \
    pos.file = "REPL";   \
    pos.text = text;


static error_t err;

static token_t *match_token(token_t *tok, const char *text, size_t *idx)
{
    if (text[*idx] == '\n')
    {
        line++;
        column = 1;
        (*idx)++;
        return match_token(tok, text, idx);
    }
    else if (isspace(text[*idx]))
    {
        (*idx)++;
        column++;
        return match_token(tok, text, idx);
    }
    else if (text[*idx] == '+')
    {
        tok->type = TOK_PLUS;
        tok->text = &text[*idx];
        tok->len = 1;
        CURRENT_POS(tok->start);

        (*idx)++;
        column++;

        CURRENT_POS(tok->end);

        return tok;
    }
    else if (text[*idx] == '-')
    {
        tok->type = TOK_MINUS;
        tok->text = &text[*idx];
        tok->len = 1;

        CURRENT_POS(tok->start);

        (*idx)++;
        column++;

        CURRENT_POS(tok->end);

        return tok;
    }
    else if (text[*idx] == '*')
    {
        tok->type = TOK_MUL;
        tok->text = &text[*idx];
        tok->len = 1;

        CURRENT_POS(tok->start);

        (*idx)++;
        column++;

        CURRENT_POS(tok->end);

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

        CURRENT_POS(tok->start);

        (*idx)++;
        column++;

        CURRENT_POS(tok->end);

        return tok;
    }
    else if (text[*idx] == ')')
    {
        tok->type = TOK_RPAREN;
        tok->text = &text[*idx];
        tok->len = 1;

        CURRENT_POS(tok->start);

        (*idx)++;
        column++;

        CURRENT_POS(tok->end);

        return tok;
    }
    else if (isdigit(text[*idx]))
    {
        tok->type = TOK_INTLIT;
        tok->text = &text[*idx];

        CURRENT_POS(tok->start);

        tok->intval = 0;
        tok->len = 0;
        while (isdigit(text[*idx]))
        {
            tok->intval *= 10;
            tok->intval += text[(*idx)++] - '0';
            column++;

            tok->len++;
        }

        CURRENT_POS(tok->end);

        return tok;
    }

    if (text[*idx] == 0)
    {
        return NULL;
    }

    err.message = "unknown token";
    CURRENT_POS(err.start);
    (*idx)++;
    column++;
    CURRENT_POS(err.end);

    set_error(&err);
    return NULL;
}

static size_t lex_index = 0;

token_t *lex(token_t *tok, const char *text)
{
    if (!text)
    {
        lex_index = 0;
        line = 1, column = 1;
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

    uint64_t old_line = line;
    uint64_t old_column = column;

    size_t idx = lex_index;
    token_t *res = match_token(tok, text, &idx);

    line = old_line;
    column = old_column;

    return res;
}
