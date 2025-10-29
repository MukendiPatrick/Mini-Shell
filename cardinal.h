/*
 * ICA10 - MiniShell
 * cardinal.h
 *
 * Shared prototypes for ICA10
 */

#ifndef CARDINAL_H
#define CARDINAL_H

// From envinspect.c
void print_env_info(void);
int spawn_and_report(void);

// From cmdrun.c
int parse_command(const char *line, char ***argv_out, char **out_path);
int run_command(char **argv, const char *out_path);

#endif
