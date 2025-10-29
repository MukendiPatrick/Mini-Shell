/*
 * ICA10 - MiniShell
 * envinspect.c
 *
 * In this file, you will print process information and demonstrate
 * process creation using fork().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// TODO: Implement this function
// Print process IDs and environment variables (USER, HOME, PATH)
void print_env_info(void)
{
    // Example output format:
    // Parent PID: 1234
    // USER=student
    // HOME=/home/student
    // PATH=/usr/bin:/bin:/usr/local/bin

    // HINT: use getpid(), getppid(), and getenv()
}

// TODO: Implement this function
// Create a child process using fork(), print messages from both processes,
// and have the parent wait for the child.
int spawn_and_report(void)
{
    // Example output:
    // I am the parent. My PID is 1234 and my child is 1235.
    // I am the child. My PID is 1235 and my parent is 1234.

    // HINT: use fork(), getpid(), getppid(), waitpid()
    return 0;
}
