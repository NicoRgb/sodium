#include <interpreter.h>
#include <assert.h>

uint64_t evaluate_binary_expr(node_t *node);
uint64_t evaluate_unary_expr(node_t *node);

static error_t err;

uint64_t evaluate(node_t *AST)
{
    switch (AST->type)
    {
    case NODE_TYPE_BINARY_EXPR:
        return evaluate_binary_expr(AST);
        break;
    case NODE_TYPE_UNARY_EXPR:
        return evaluate_unary_expr(AST);
        break;
    default:
        assert(false);
    }
    return 0;
}

#define EVALUATE(n)     \
    ({                  \
        uint64_t _res = (evaluate(n)); \
        if (is_error()) \
            return 0;   \
        _res;           \
    })

uint64_t evaluate_binary_expr(node_t *node)
{
    switch (node->tok->type)
    {
    case TOK_PLUS:
        return EVALUATE(node->left) + EVALUATE(node->right);
    case TOK_MINUS:
        return -EVALUATE(node->left) - EVALUATE(node->right);
    case TOK_MUL:
        return EVALUATE(node->left) * EVALUATE(node->right);
    case TOK_DIV:
    {
        uint64_t divisor = EVALUATE(node->right);
        if (divisor == 0)
        {
            err.start = node->start;
            err.end = node->end;
            err.message = "RUNTIME ERROR -> division by zero";

            set_error(&err);
            return 0;
        }

        return -EVALUATE(node->left) / divisor;
    }
    default:
        assert(false);
    }

    return 0;
}

uint64_t evaluate_unary_expr(node_t *node)
{
    switch (node->tok->type)
    {
    case TOK_INTLIT:
        return node->tok->intval;
    case TOK_PLUS:
        return EVALUATE(node->left);
    case TOK_MINUS:
        return -EVALUATE(node->left);
    default:
        assert(false);
    }

    return 0;
}
