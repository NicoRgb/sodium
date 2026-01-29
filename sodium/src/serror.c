#include <serror.h>

#include <stdio.h>
#include <ctype.h>

void render_template(position_t *start, position_t *end)
{
    uint64_t start_idx = start->index - (start->column - 1);

    printf("%ld\t| ", start->line);
    for (uint64_t i = 0; isprint(start->text[i]) && start->text[i] != '\n'; i++)
    {
        if (i >= start->column - 1 && i < end->column - 1)
        {
            printf("\033[0;31m");
        }
        putc(start->text[i+start_idx], stdout);
        printf("\033[0m");
    }

    printf("\n\t| ");

    for (uint64_t i = 0; i < start->column - 1; i++)
    {
        printf(" ");
    }

    for (uint64_t i = start->column - 1; i < end->column - 1; i++)
    {
        printf("\033[0;31m^\033[0m");
    }

    printf("\n");
}

void print_error(error_t *error)
{
    printf("%s:%ld:%ld: \033[0;31merror:\033[0m %s\n", error->start.file, error->start.line, error->start.column, error->message);
    render_template(&error->start, &error->end);
}

static error_t *err = NULL;

void set_error(error_t *error)
{
    err = error;
}

error_t *get_error(void)
{
    return err;
}

void unset_error(void)
{
    err = NULL;
}

bool is_error(void)
{
    return err != NULL;
}
