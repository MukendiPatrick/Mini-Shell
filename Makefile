# ICA10 - MiniShell
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Default build targets
all: envinspect cmdrun

envinspect: envinspect.c main_env.c
	$(CC) $(CFLAGS) -o envinspect envinspect.c main_env.c

cmdrun: cmdrun.c main_cmd.c
	$(CC) $(CFLAGS) -o cmdrun cmdrun.c main_cmd.c

# Clean up build and output files
clean:
	rm -f envinspect cmdrun out.txt report.txt

# Run the provided test script
test: all
	@echo "=================================="
	@echo " Running ICA10-MiniShell Tests "
	@echo "=================================="
	@bash test.sh

# Declare phony targets so make doesn’t confuse them with files
.PHONY: all clean test
