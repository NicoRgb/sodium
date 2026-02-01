#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <stdint.h>
#include <stddef.h>

#include <parser.h>

uint64_t evaluate(node_t *AST);

#endif