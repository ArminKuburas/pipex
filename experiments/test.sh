#!/bin/bash

echo "This is the content of infile" > infile
echo "Another line of content" >> infile
echo "And another line of content" >> infile
echo "And another line of content for fun" >> infile



tests=(
  "infile 'ls -l' 'wc -l' outfile1"
  "file_does_not_exist 'ls -l' 'sleep 5' outfile2"
  "file_does_not_exist 'sleep 10' 'echo hello' outfile3"
  "file_does_not_exist 'echo hello' 'sleep 5' outfile4"
)
for test in "${tests[@]}"; do
  eval "./pipex $test"

  echo "-----------------------------"
done