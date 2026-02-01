#ifndef _PARSER_H
#define _PARSER_H

#include <stdint.h>
#include <stddef.h>

#include <lexer.h>

typedef enum
{
    NODE_TYPE_BINARY_EXPR,
    NODE_TYPE_UNARY_EXPR,
} node_type_t;

typedef struct _node
{
    node_type_t type;
    struct _node *left;
    struct _node *right;
    token_t *tok;

    position_t start, end;
} node_t;

void print_ast(node_t *ast);
node_t *parse(const char *text);

#endif