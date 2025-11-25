# MiniShell

MiniShell is a personal project, built to explore how Linux manages processes, environment variables, and command execution. It consists of small C programs and a Bash script that demonstrate process creation, command execution, and output redirection, similar to how a minimal shell works. This project helped me understand how shells interact with the OS at a low level.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Linux Environment Setup](#linux-environment-setup)
- [Project Features](#project-features)
- [Processes, Exec, and Redirection](#processes-exec-and-redirection)
- [Implementation Details](#implementation-details)
  - [envinspect.c](#envinspectc)
  - [cmdrun.c](#cmdrunc)
  - [system_report.sh](#system_reportsh)
- [Project Files](#project-files)
- [Building and Testing](#building-and-testing)
- [Example Usage](#example-usage)

---

## Project Overview

MiniShell is a hands-on project for learning core Linux programming concepts:

- Understanding processes, PIDs, and parent-child relationships.
- Accessing environment variables from C programs.
- Executing commands from a minimal shell prompt with optional output redirection.
- Writing Bash scripts that summarize system information and redirect output.

This project simulates basic shell behavior and demonstrates how programs interact with the Linux OS.

---

## Linux Environment Setup

MiniShell runs on Linux. Recommended setups:

**Windows + WSL2**

```bash
sudo apt update
sudo apt install -y build-essential
gcc --version

**macOS/Chromebook + Docker**

```bash
docker run -it --name minishell -v "$PWD":/hw -w /hw ubuntu bash
apt update && apt install -y build-essential bash
gcc --version
```

---

## Project Features

* **Process and environment inspection:** View PIDs, PPIDs, and environment variables.
* **Minimal command runner:** Parse and execute commands with optional `>` output redirection.
* **System reporting script:** Quickly summarize system info and processes for the current user.

---

## Processes, Exec, and Redirection

* **Processes:** Each running program has its own memory and environment.
* **fork():** Creates a nearly identical child process.
* **execvp():** Replaces a process image with a new program.
* **I/O Redirection:** Redirect `stdout` to a file using `dup2()` (e.g., `command > file.txt`).

**Example command with redirection:**

```bash
cmd> ls -l > out.txt
```

* The output of `ls -l` is written to `out.txt`.
* The parent process waits for the child process to finish.

---

## Implementation Details

### envinspect.c

* **print_env_info():** Prints the current process PID, parent PID, and key environment variables: `USER`, `HOME`, `PATH`.
* **spawn_and_report():** Demonstrates `fork()`.

  * Parent prints: `I am the parent. My PID is <P> and my child is <C>.`
  * Child prints: `I am the child. My PID is <C> and my parent is <P>.`
  * Parent waits for the child to finish using `waitpid()`.

### cmdrun.c

* **parse_command():** Splits a command line into arguments (`argv`) for `execvp()`, detects optional output redirection (`>`). Handles one redirection, ignores extra spaces, and does not support piping or input redirection.
* **run_command():** Executes the parsed command using `fork()` + `execvp()`.

  * If output redirection is specified, opens the file using `open(out_path, O_CREAT|O_WRONLY|O_TRUNC, 0644)` and duplicates the file descriptor to `STDOUT_FILENO` using `dup2()`.
  * The parent waits for the child and returns the exit status.
  * Prints errors using `perror()`.

### system_report.sh

* Bash script to print a simple system summary:

```bash
#!/bin/bash
echo "System Report for $USER"
date
echo "Processes running: $(ps -u "$USER" | wc -l)"
```

* Make it executable:

```bash
chmod +x system_report.sh
```

---

## Project Files

* `envinspect.c` – Implements process and environment inspection.
* `cmdrun.c` – Implements the minimal command runner.
* `system_report.sh` – Bash script for system summary.
* `main_env.c` – Driver program for envinspect.
* `main_cmd.c` – Driver program for cmdrun.
* `cardinal.h` – Shared function prototypes and small helpers.
* `Makefile` – Build targets for `envinspect`, `cmdrun`, and `all`.
* `test.sh` – Script to validate program functionality.

---

## Building and Testing

**Compile the programs:**

```bash
make
```

**Run the test script:**

```bash
make test
```

**Run the programs directly:**

```bash
./envinspect             # Run environment inspector demo
./cmdrun                 # Launch the minimal shell prompt 'cmd>'
bash system_report.sh    # Print system report
bash system_report.sh > report.txt  # Save report to a file
```

---

## Example Usage

**envinspect.c output:**

```bash
$ ./envinspect
Process Info:
PID: 1234
PPID: 1233
USER: user
HOME: /home/user
PATH: /usr/local/bin:/usr/bin:/bin
```

**cmdrun.c with output redirection:**

```bash
cmd> ls -l > files.txt
# Output of ls is written to files.txt
```

**system_report.sh output:**

```bash
$ bash system_report.sh
System Report for user
Mon Nov 25 14:32:00 UTC 2025
Processes running: 7
```
