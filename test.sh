#!/bin/bash
# ICA10 - MiniShell - test script (simplified placeholder)
# DO NOT MODIFY THIS FILE.

echo "Running basic tests..."

echo
echo "[1] Testing envinspect..."
./envinspect

echo
echo "[2] Testing cmdrun (simple command)..."
echo "ls -l" | ./cmdrun

echo
echo "[3] Testing cmdrun (with redirection)..."
echo "ls > out.txt" | ./cmdrun
echo "Contents of out.txt:"
cat out.txt

echo
echo "[4] Testing system_report.sh..."
bash system_report.sh

echo
echo "All tests complete."