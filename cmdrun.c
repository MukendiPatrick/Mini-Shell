/*
 * ICA10 - MiniShell
 * cmdrun.c
 *
 * In this file, you will parse a user command and execute it
 * using fork() and execvp(), with optional output redirection (>).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_ARGS 64

// TODO: Implement this function
// Parse a single command line into argv[] and detect optional output redirection (>).
int parse_command(const char *line, char ***argv_out, char **out_path)
{
    // Line copy
    char line_copy[256];
    strncpy(line_copy, line, sizeof(line_copy) - 1);
    line_copy[strcspn(line_copy, "\n")] = '\0';

    // Get the number of commands or argc by counting
    // the number of spaces in the command line
    int argc = 0;
    int dup_spaces = 0;
    for (int i = 0; line_copy[i] != '\0'; i++)
    {
        if (line_copy[i] != ' ' && line_copy[i] != '\t')
        {
            if (!dup_spaces)
            {
                dup_spaces = 1;
                argc++;
            }
        }
        else
        {
            dup_spaces = 0;
        }
    }

    // Return 1 (Error) if no arguments
    if (argc == 0)
        return 1;

    // Allocate memory for argv_out
    *argv_out = malloc((argc + 1) * sizeof(char *));
    if (!*argv_out)
        return 1;

    int index = 0;
    // Split command line
    char *token = strtok(line_copy, " \t");
    while (token)
    {
        if (strcmp(token, ">") == 0)
        {
            // Next should be filename
            token = strtok(NULL, " \t");
            if (token)
            {
                // allocate memory for out_path inline
                *out_path = malloc(strlen(token) + 1);
                if (!*out_path)
                {
                    return 1;
                }
                strcpy(*out_path, token);
            }
            break;
        }
        else
        {
            // allocate memory for argv_out[index] inline
            (*argv_out)[index] = malloc(strlen(token) + 1);
            if (!(*argv_out)[index])
            {
                return 1;
            }
            strcpy((*argv_out)[index], token);
            index++;
        }
        token = strtok(NULL, " \t");
    }
    (*argv_out)[index] = NULL; // NULL terminate argv

    return 0;
}

// TODO: Implement this function
// Fork and execute the command, handling optional output redirection.
int run_command(char **argv, const char *out_path)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork\n");
        return 1;
    }

    if (pid == 0)
    {
        // --- Child process ---
        if (out_path != NULL)
        {
            int fd = open(out_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(argv[0], argv);
        perror("execvp failed");
        return 1;
    }

    // --- Parent process ---
    int status;
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("Error: waitpid");
        return 1;
    }

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return 1;

    return 0;
}
