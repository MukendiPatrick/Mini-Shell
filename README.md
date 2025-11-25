# MiniShell

MiniShell is a lightweight project I built to explore how Linux manages processes, environment variables, and command execution. It consists of small C programs and a Bash script that demonstrate process creation, command execution, and output redirection, similar to how a minimal shell works.

---

## Table of Contents

- [Project Overview](#project-overview)  
- [Linux Environment Setup](#linux-environment-setup)  
- [Project Features](#project-features)  
- [Implementation Details](#implementation-details)  
  - [envinspect.c](#envinspectc)  
  - [cmdrun.c](#cmdrunc)  
  - [system_report.sh](#system_reportsh)  
- [Project Files](#project-files)  
- [Building and Testing](#building-and-testing)  

---

## Project Overview

MiniShell is designed to give hands-on experience with core Linux concepts:

- Understanding processes, PIDs, and parent-child relationships.  
- Learning how environment variables are accessed in C programs.  
- Executing commands from a minimal shell prompt with optional output redirection.  
- Writing simple Bash scripts that interact with the system and redirect output.

The project is a great way to see how shells work under the hood and practice low-level Linux programming.

---

## Linux Environment Setup

MiniShell runs on Linux. Recommended setups:

**Windows + WSL2**

```bash
# Install Ubuntu via Microsoft Store
sudo apt update
sudo apt install -y build-essential

# Verify installation
gcc --version
