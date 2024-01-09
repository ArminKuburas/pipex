#!/bin/bash

# Create input files
echo "This is a test input file." > input
echo "Another test input." > not_working_input
chmod 000 not_working_input

# Create output files
touch output
touch output2
touch not_working_output
chmod 000 not_working_output

# Test case: Ensure pipex takes exactly 5 inputs
echo "Testing if pipex takes exactly 5 inputs"
./pipex 1 2 3
./pipex 1 2 3 4 5

# Test case: Basic test
echo "Basic test: pipex input 'ls -l' cat output"
./pipex input "ls -l" cat output
cat output

echo "Versus the terminal: < input ls -l | cat > output"
< input ls -l | cat > output2
cat output2
# Clean up temporary files
rm input not_working_input output output2 not_working_output
