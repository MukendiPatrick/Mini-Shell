# ICA10-MiniShell

In this assignment, you’ll build small tools that expose how Linux runs programs: a process/environment inspector in C, a tiny command runner that uses `fork()`/`exec()` and I/O redirection, and a short shell script. You will complete this work in a Linux environment (lab VM, WSL2, or Docker), so that the correct system calls and behavior are available.

You’ll be given simple drivers and tests. Your job is to implement the required C functions and script so the tests pass and you learn how shells interact with the OS.

## Linux Environment

You must run this assignment on Linux:

### Windows + WSL2

1. Install WSL and Ubuntu from Microsoft Store.
2. In Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential
```

### macOS/Chromebook + Docker

1. Install Docker Desktop.
2. Start a container and install tools:

```bash
docker run -it --name minishell -v "$PWD":/hw -w /hw ubuntu bash
apt update && apt install -y build-essential bash
```

To double check your installation is correct, `gcc --version` prints a version number.

## To Do

You will implement three small deliverables:

* `envinspect.c` (C): print process IDs and key environment variables; demonstrate `fork()`.
* `cmdrun.c` (C): read a command line, optionally handle `>` output redirection, create a child with `fork()`, and execute with `execvp()`.
* `system_report.sh` (Bash): a tiny script that prints a system summary and demonstrates redirection/vars.

## Processes, Exec, Redirection

A **process** is a running program with its own address space and environment. When a process calls `fork()`, the OS creates a child process that is (nearly) a copy of the parent. The child can then replace its image with a new program using the `exec*` family (e.g., `execvp()`), inheriting open file descriptors and environment variables.

**I/O redirection** (e.g., `>`): shells open the target file, duplicate the file descriptor onto standard streams using `dup2()`, then run the program. Your `cmdrun.c` will implement the essential pieces of this behavior.

### Example

If the user enters:

```shell
cmd> ls -l > out.txt
```

Your program should detect `> out.txt`, redirect the child’s `stdout` to `out.txt`, and then run `ls -l` in that child. The parent waits for completion.

## Implementation

### `envinspect.c`

In `envinspect.c`, you will implement two functions.
The first, `print_env_info()`, prints the process’s PID and PPID along with the `USER`, `HOME`, and `PATH` environment variables using `getpid()`, `getppid()`, and `getenv()`.
The second, `spawn_and_report()`, demonstrates process creation using `fork()`. The parent process should print:
`I am the parent. My PID is <P> and my child is <C>.`
and the child should print:
`I am the child. My PID is <C> and my parent is <P>.`
The parent must wait for the child with `waitpid()` before exiting. Return `0` on success and a nonzero value on error.

---

### `cmdrun.c`

In `cmdrun.c`, you will build a minimal command runner that parses and executes user input.
`parse_command()` splits a command line into an argument vector for `execvp()` and detects an optional output redirection (`>`). It supports one redirection of the form `command > filename`, ignores extra spaces, and does not handle piping or input redirection. On success, it should allocate a NULL-terminated `argv` array and return `0`. On error (e.g., missing filename after `>`), return nonzero.

`run_command()` uses `fork()` and `execvp()` to execute the parsed command. If an output file is given, open it with `open(out_path, O_CREAT|O_WRONLY|O_TRUNC, 0644)` and redirect output with `dup2(fd, STDOUT_FILENO)`. The parent waits using `waitpid()` and returns the child’s exit status. Print errors with `perror()` and return nonzero on failure.

---

### `system_report.sh`

In `system_report.sh`, write a simple Bash script that prints a short system summary. It should display the current user, date/time, and the number of running processes owned by that user. The output should match the format below and can be redirected into a file (e.g., `bash system_report.sh > report.txt`):

```bash
#!/bin/bash
echo "System Report for $USER"
date
echo "Processes running: $(ps -u "$USER" | wc -l)"
```

Remember to make the script executable with `chmod +x system_report.sh`.

## Files

* `envinspect.c` – Implement `print_env_info()` and `spawn_and_report()`.
* `cmdrun.c` – Implement `parse_command()` and `run_command()`.
* `system_report.sh` – Bash script as described (remember `chmod +x`).
* `main_env.c` – Driver for envinspect (don’t modify).
* `main_cmd.c` – Driver for cmdrun (don’t modify).
* `cardinal.h` – Shared prototypes and small helpers (don’t modify).
* `Makefile` – Build targets `envinspect`, `cmdrun`, and `all`.
* `test.sh` – Script to validate output/behavior.
* `README.md` – This file.

(Your course repo includes `main_env.c`, `main_cmd.c`, `cardinal.h`, `Makefile`, and `test.sh`.)

## Testing

Your implementation will be run against `test.sh`. To complete this assignment, you must pass all test sections:

* Section 1: tests `print_env_info()`
* Section 2: tests `spawn_and_report()`
* Section 3: tests `parse_command()` and `run_command()` (normal run)
* Section 4: tests `run_command()` with `>` redirection
* Section 5: tests `system_report.sh`

To compile:

```shell
make
```

To run the tests:

```shell
make test
```

You can also run the drivers directly:

```shell
./envinspect             # runs env inspector demo
./cmdrun                 # launches the command prompt 'cmd>'
bash system_report.sh    # prints to stdout; try: bash system_report.sh > report.txt
```

## Hints

* Work one function at a time. Verify with small manual tests before running `make test`.
* Useful headers:
  `#include <stdio.h>`, `<stdlib.h>`, `<string.h>`, `<unistd.h>`, `<sys/types.h>`, `<sys/wait.h>`, `<fcntl.h>`, `<errno.h>`
* Tokenizing input: `strtok()` (or `strtok_r()`); be careful to preserve the filename after `>`.
* Allocating `argv`: count tokens first, then `malloc` a `char*` array sized `count+1`, ending with `NULL`.
* Redirection: open the file, `dup2(fd, STDOUT_FILENO)`, then close the original `fd`.
* In C, strings are char arrays ending with `'\0'`. Always terminate `argv` with `NULL` for `execvp()`.
