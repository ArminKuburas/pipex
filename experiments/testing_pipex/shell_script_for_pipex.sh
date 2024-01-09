#!/bin/bash

# Create input files
echo "This is a test input file." > input
echo "Another test input." > not_working_input
chmod 000 not_working_input

# Create output files
touch output output2 not_working_output
chmod 000 not_working_output

# Test case: Ensure pipex takes exactly 5 inputs
echo "Testing if pipex takes exactly 5 inputs"
./pipex 1 2 3
./pipex 1 2 3 4 5

# Test case: Basic test
echo "Basic test: pipex input 'ls -l' cat output"
./pipex input "ls -l" cat output
cat output

echo "Versus the terminal: < input ls -l | cat > output2"
< input ls -l | cat > output2
cat output2

# Test case: Basic test 2: What if there is no input file?
echo "Test case: Basic test 2: What if there is no input file?"
echo "Basic test 2: pipex input 'ls -l' 'echo hello' output"
./pipex input "ls -l" "echo hello" output
cat output

echo "Versus the terminal: < input ls -l | echo hello > output2"
< input ls -l | echo hello > output2
cat output2

# Test case: Basic test 3: What if there is no output file?
echo "Test case: Basic test 3: What if there is no output file?"
echo "Basic test 3: pipex input 'ls -l' 'echo hello' output3"
./pipex input "ls -l" "echo hello" output3
cat output3

echo "Versus the terminal: < input ls -l | echo hello > output4"
< input ls -l | echo hello > output4
cat output4

# Test case: Basic test 4: Let's try a few different commands!
echo "Test case: Basic test 4: Let's try a few different commands!"
echo './pipex input "grep hello" "cat" output'
./pipex input "grep hello" "cat" output
cat output

echo './pipex input "grep goodbye" "cat" output'
./pipex input "grep goodbye" "cat" output
cat output

echo './pipex input "grep goodbye" "wc -l" output'
./pipex input "grep goodbye" "wc -l" output
cat output

echo './pipex input "grep hello" "wc -l" output'
./pipex input "grep hello" "wc -l" output
cat output

echo './pipex input "ls -l" "wc -l" output'
./pipex input "ls -l" "wc -l" output
cat output

while true; do
    # Prompt the user for more tests
    read -p "Do you want to do more tests? (y/n): " answer
    case $answer in
        [Yy]* )
			echo "Great choice! Lets do it!" 
			echo "--------------------------"
			# Extreme test 1: What happens if you try a input file whose permissions you do not have?
			echo "Extreme test 1: What happens if you try a input file whose permissions you do not have?"
			echo './pipex not_working_input ls "echo hello2" output'
			./pipex not_working_input ls "echo hello2" output
			cat output
			echo 'Versus the Terminal: < not_working_input ls | echo hello3 > output'
			< not_working_input ls | echo hello3 > output
			cat output
			# Extreme test 2: What happens if you try a output file whose permissions you do not have?
			echo "Extreme test 2: What happens if you try a output file whose permissions you do not have?"
			echo './pipex input ls "echo hello7" not_working_output'
			./pipex input ls "echo hello7" not_working_output
			cat not_working_output
			echo 'Versus the Terminal: < input ls | echo hello17 > not_working_output '
			< input ls | echo hello17 > not_working_output 
			cat not_working_output
			# Extreme test 3: What happens if we change permissions while doing the pipe?
			echo "Extreme test 3: What happens if we change permissions while doing the pipe?"
			echo './pipex input "chmod 000 output" "echo wow" output'
			./pipex input "chmod 000 output" "echo wow" output
			chmod 777 output
			cat output
			echo 'Versus the Terminal: < input chmod 000 output | echo "wow it still does it!" > output'
			< input chmod 000 output | echo "wow it still does it!" > output
			chmod 777 output
			cat output
			echo "Nice now let's see how you can handle a hostile environment and commands where you do not have the permission to use em!" 
			break;;
        [Nn]* ) 
			echo "Ahhh too sad! Hope you change your mind because these can be pretty fun :>"
			break;;
        * ) echo "Please enter 'y' for yes or 'n' for no.";;
    esac
done

# Clean up temporary files
rm -f input not_working_input output output2 not_working_output output3 output4
