#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> // for getopt

struct
{
    bool verbose_output;
    char *input_file;
} compiler_options;

void parse_arguments(int argc, char **argv)
{
    compiler_options.verbose_output = false;
    compiler_options.input_file = NULL;

    /*
     -h for help
     -u for usage
     -v for verbose
     -e for evaluate
    */

    int option = 0;
    while ((option = getopt(argc, argv, ":huve:")) != -1)
    {
        switch (option)
        {
        case ':':
        {
            fprintf(stderr, "critical failure: option '-%c' is not used correctly\nuse '-h' for usage information\n", optopt);
            exit(1);
        }
        case '?':
        {
            fprintf(stderr, "critical failure: option '-%c' not recognized\nuse '-h' for usage information\n", optopt);
            exit(1);
        }
        case 'h':
        case 'u':
        {
            printf("usage: sodium [file]?\n\t-h: show this message\n\t-u: show this message\n\t-v: verbose output\n\t-e [file]: evalute file\n");
            exit(0);
        }
        case 'v':
        {
            compiler_options.verbose_output = true;
            break;
        }
        case 'e':
        {
            compiler_options.input_file = strdup(optarg);
            break;
        }
        }

        if (optind > 1 && argc > 1 && optind >= argc)
        {
            return;
        }
    }

    if (optind + 1 < argc || (compiler_options.input_file != NULL && optind < argc))
    {
        fprintf(stderr, "warning: use of multiple unnamed arguments or of an unnamed argument in combination with a -e option -> some files will be ignored\n");
    }

    if (compiler_options.input_file == NULL && optind < argc)
    {
        compiler_options.input_file = strdup(argv[optind]);
    }
}

int main(int argc, char **argv)
{
    parse_arguments(argc, argv);
    if (compiler_options.verbose_output && compiler_options.input_file != NULL)
    {
        printf("evaluating file '%s'\n", compiler_options.input_file);
    }

    free(compiler_options.input_file);
    return 0;
}
