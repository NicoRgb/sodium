#include <lexer.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

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

static size_t index = 0;

token_t *lex(token_t *tok, const char *text)
{
    if (!text)
    {
        index = 0;
        return NULL;
    }

    assert(tok);
    assert(text);

    if (!text[index])
    {
        return NULL;
    }

    return match_token(tok, text, &index);
}

token_t *peek(token_t *tok, const char *text)
{
    assert(tok);
    assert(text);

    if (!text[index])
    {
        return NULL;
    }

    size_t idx = index;
    return match_token(tok, text, &idx);
}
