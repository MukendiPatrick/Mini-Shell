#!/bin/bash
# ICA10 - MiniShell
# system_report.sh
#

echo "System Report for $USER"
date
echo "Processes running: $(ps -u "$USER" | wc -l)"