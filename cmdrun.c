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
    // Example:
    // Input: "ls -l > out.txt"
    // argv_out -> ["ls", "-l", NULL]
    // out_path -> "out.txt"
    //
    // HINTS:
    // - Use strtok() or strtok_r() to split by spaces
    // - Detect the '>' token and record the following filename
    // - Allocate memory for argv and out_path
    // - Return 0 on success, nonzero on parse error
    return 0;
}

// TODO: Implement this function
// Fork and execute the command, handling optional output redirection.
int run_command(char **argv, const char *out_path)
{
    // Example behavior:
    // cmd> ls -l > listing.txt
    //
    // HINTS:
    // - In child: if out_path != NULL, open file with open()
    //   and redirect stdout using dup2()
    // - Call execvp(argv[0], argv)
    // - In parent: wait for the child (waitpid)
    // - Return child's exit status or nonzero on error
    return 0;
}
