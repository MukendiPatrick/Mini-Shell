/*
 * ICA10 - MiniShell
 * main_env.c
 *
 * Driver for envinspect.c
 * DO NOT MODIFY THIS FILE.
 */

#include <stdio.h>
#include "cardinal.h"

int main(void)
{
    printf("=== Environment Info ===\n");
    print_env_info();

    printf("\n=== Process Fork Test ===\n");
    spawn_and_report();

    return 0;
}
