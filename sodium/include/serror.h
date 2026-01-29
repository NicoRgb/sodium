#ifndef _SERROR_H
#define _SERROR_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct
{
    uint64_t line, column;
    uint64_t index;
    const char *file, *text;
} position_t;

void render_template(position_t *start, position_t *end);

typedef struct
{
    const char *message;
    position_t start, end;
} error_t;

void print_error(error_t *error);

void set_error(error_t *error);
error_t *get_error(void);
void unset_error(void);
bool is_error(void);

#endif