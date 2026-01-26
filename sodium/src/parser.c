#include <parser.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static token_t tok;
static const char *text;

static void print_token(token_t *tok)
{
    printf("%s: '%.*s', %ld\n", TOKEN_NAMES[tok->type], (int)tok->len, tok->text, tok->intval);
}

static void print_ast_indent(node_t *ast, uint8_t indent)
{
    if (!ast)
    {
        for (uint8_t i = 0; i < indent+2; i++) printf(" ");
        printf("NULL\n");
        return;
    }

    switch (ast->type)
    {
    case NODE_TYPE_BINARY_EXPR:
        for (uint8_t i = 0; i < indent; i++) printf(" ");
        printf("BINARY EXPR\n");
        print_ast_indent(ast->left, indent+2);
        if (ast->tok)
        {
            for (uint8_t i = 0; i < indent+2; i++) printf(" ");
            print_token(ast->tok);

            print_ast_indent(ast->right, indent+2);
        }
        break;

    case NODE_TYPE_UNARY_EXPR:
        for (uint8_t i = 0; i < indent; i++) printf(" ");
        printf("UNARY EXPR\n");

        for (uint8_t i = 0; i < indent+2; i++) printf(" ");
        print_token(ast->tok);

        if (ast->left)
        {
            print_ast_indent(ast->left, indent+2);
        }
        break;
    
    default:
        for (uint8_t i = 0; i < indent+2; i++) printf(" ");
        printf("UNKNOWN NODE TYPE\n");
        break;
    }
}

void print_ast(node_t *ast)
{
    print_ast_indent(ast, 0);
}

static node_t *node_create(void)
{
    node_t *res = malloc(sizeof(node_t));
    memset(res, 0, sizeof(node_t));
    return res;
}

static node_t *binary_expression(node_t *(func)(void), token_type_t op1, token_type_t op2)
{
    node_t *left = func();

    peek(&tok, text);
    while (tok.type == op1 || tok.type == op2)
    {
        node_t *node = node_create();
        node->type = NODE_TYPE_BINARY_EXPR;
        node->left = left;
        node->tok = token_clone(lex(&tok, text));
        node->right = func();

        left = node;

        peek(&tok, text);
    }

    return left;
}

static node_t *expr(void);
static node_t *additive_expr(void);
static node_t *multiplicative_expr(void);
static node_t *primary(void);
static node_t *unary_expr(void);

node_t *parse(const char *t)
{
    text = t;
    return expr();
}

static node_t *expr(void)
{
    return additive_expr();
}

static node_t *additive_expr(void)
{
    return binary_expression(multiplicative_expr, TOK_PLUS, TOK_MINUS);
}

static node_t *multiplicative_expr(void)
{
    return binary_expression(primary, TOK_MUL, TOK_DIV);
}

static node_t *primary(void)
{
    return unary_expr();
}

static node_t *unary_expr(void)
{
    peek(&tok, text);
    if (tok.type == TOK_INTLIT)
    {
        node_t *node = node_create();
        node->type = NODE_TYPE_UNARY_EXPR;
        node->tok = token_clone(lex(&tok, text));
        return node;
    }
    else if (tok.type == TOK_PLUS || tok.type == TOK_MINUS)
    {
        node_t *node = node_create();
        node->type = NODE_TYPE_UNARY_EXPR;
        node->tok = token_clone(lex(&tok, text));
        node->left = unary_expr();
        return node;
    }

    return NULL;
}
