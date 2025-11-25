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
    pid_t pip = getpid();
    pid_t ppid = getppid();
    char *user = getenv("USER");
    char *home = getenv("HOME");
    char *path = getenv("PATH");

    if (ppid > 0)
    {
        printf("Parent PID: %d\n", ppid);
    }
    else
    {
        printf("Error getting ppid.\n");
        return;
    }

    if (pip > 0)
    {
        printf("Current PID: %d\n", pip);
    }
    else
    {
        printf("Error getting pid.\n");
        return;
    }

    if (user != NULL)
    {
        printf("USER=%s\n", user);
    }
    else
    {
        printf("USE envivonment variable is not set.\n");
        return;
    }

    if (home != NULL)
    {
        printf("HOME=%s\n", home);
    }
    else
    {
        printf("HOME envivonment variable is not set.\n");
        return;
    }

    if (path != NULL)
    {
        printf("PATH=%s\n", path);
    }
    else
    {
        printf("PATH envivonment variable is not set.\n");
        return;
    }

    return;
}

// TODO: Implement this function
// Create a child process using fork(), print messages from both processes,
// and have the parent wait for the child.
int spawn_and_report(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed");
        return -1;
    }

    if (pid == 0)
    {
        pid_t child_pid = getpid();
        pid_t ppid = getppid();
        printf("I am the child. My PID is %d and my parent is %d.\n", child_pid, ppid);
        return 0;
    }
    else
    {
        int fork_status;
        // Wait for the child before exiting.
        pid_t wait_child = waitpid(pid, &fork_status, 0);

        if (wait_child == -1)
        {
            printf("Error waiting for child");
            return -1;
        }

        if (WIFEXITED(fork_status))
        {
            pid_t ppid = getpid();
            printf("I am the parent. My PID is %d and my child is %d.\n", ppid, pid);
        }
        else
        {
            printf("Error waiting for child");
            return -1;
        }
    }
    return 0;
}
