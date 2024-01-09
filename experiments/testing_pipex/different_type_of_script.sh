#!/bin/bash

function run_test() {
    local test_name="$1"
    local command="$2"
	local kitten="$3"

    echo "Running test: $test_name"
    echo "$command"
    eval "$command"
	echo $?
	if [ -n "$kitten" ]; then
    	cat "$kitten"
	fi
	while true; do
    	read -p "Do you want to continue to the next test? (y/n): " answer
    	case $answer in
        	[Yy]* ) break;;
        	[Nn]* )
				echo "oops must of been a typo!" 
				continue;;
        	* ) echo "Please enter 'y' for yes or 'n' for no.";;
    esac
done
}

# Create input files
echo "This is a test input file." > input
echo "Another test input." > not_working_input
chmod 000 not_working_input

# Create output files
touch output output2 not_working_output
chmod 000 not_working_output

# Test case: Ensure pipex takes exactly 5 inputs
run_test "Test case: Ensure pipex takes exactly 5 inputs" "./pipex 1 2 3"
run_test "Test case: Ensure pipex takes exactly 5 inputs" "./pipex 1 2 3 4 5"

# Test case: Basic test
run_test "Test case: Basic test" "./pipex input 'ls -l' cat output" "output"
run_test "Versus the terminal" "< input ls -l | cat > output2" "output"

# Test case: Basic test 2: What if there is no input file?
run_test "Test case: Basic test 2: What if there is no input file?" "./pipex input 'ls -l' 'echo hello' output" "output"
run_test "Versus the terminal" "< input ls -l | echo hello > output2" "output"

# Test case: Basic test 3: What if there is no output file?
run_test "Test case: Basic test 3: What if there is no output file?" "./pipex input 'ls -l' 'echo hello' output3" "output3"
run_test "Versus the terminal" "< input ls -l | echo hello > output4" "output4"

# Test case: Basic test 4: Let's try a few different commands!
run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep hello' 'cat' output" "output"
run_test "Versus the terminal" "< input grep hello | cat > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep goodbye' 'cat' output" "output"
run_test "Versus the terminal" "< input grep goodbye | cat > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep goodbye' 'wc -l' output" "output"
run_test "Versus the terminal" "< input grep goodbye | wc -l > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'grep hello' 'wc -l' output" "output"
run_test "Versus the terminal" "< input grep hello | wc -l > output2" "output2"

run_test "Test case: Basic test 4: Let's try a few different commands!" "./pipex input 'ls -l' 'wc -l' output" "output"
run_test "Versus the terminal" "< input ls -l | wc -l > output2" "output"

while true; do
    read -p "Do you want to continue to the next test? (y/n): " answer
    case $answer in
        [Yy]* ) break;;
        [Nn]* ) 
				echo "oops must of been a typo!"
				continue;;
        * ) echo "Please enter 'y' for yes or 'n' for no.";;
    esac
done

# Extreme test 1: What happens if you try an input file whose permissions you do not have?
run_test "Extreme test 1: What happens if you try an input file whose permissions you do not have?" "./pipex not_working_input 'ls' 'echo hello2' output" "output"
run_test "Versus the terminal" "< not_working_input ls | echo hello3 > output2" "output2"

# Extreme test 2: What happens if you try an output file whose permissions you do not have?
run_test "Extreme test 2: What happens if you try an output file whose permissions you do not have?" "./pipex input 'ls' 'echo hello7' not_working_output" "not_working_output"
run_test "Versus the terminal" "< input ls | echo hello17 > not_working_output" "not_working_output"

# Extreme test 3: What happens if we change permissions while doing the pipe?
run_test "Extreme test 3: What happens if we change permissions while doing the pipe?" "./pipex input 'chmod 000 output' 'echo wow' output" "output"
chmod 777 output
run_test "Versus the terminal" "< input chmod 000 output | echo 'wow it still does it!' > output2" "output2"

echo "Thats it! Now its time to test out how you handle a hostile environment and hostile functions!"
# Clean up temporary files
rm -f input not_working_input output output2 not_working_output output3 output4
