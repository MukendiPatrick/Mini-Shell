/*
 * ICA10 - MiniShell
 * main_cmd.c
 *
 * Driver for cmdrun.c
 * DO NOT MODIFY THIS FILE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cardinal.h"

int main(void)
{
    char line[256];
    printf("cmd> ");

    // Simple REPL-style loop
    while (fgets(line, sizeof(line), stdin))
    {
        if (strncmp(line, "exit", 4) == 0)
            break;

        char **argv = NULL;
        char *out_path = NULL;

        if (parse_command(line, &argv, &out_path) == 0)
        {
            run_command(argv, out_path);
        }
        else
        {
            printf("Error parsing command.\n");
        }

        // Free allocated memory (students should handle this properly)
        if (argv)
        {
            for (int i = 0; argv[i]; i++)
                free(argv[i]);
            free(argv);
        }
        free(out_path);

        printf("cmd> ");
    }

    printf("Exiting minishell.\n");
    return 0;
}
