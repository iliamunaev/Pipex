#!/usr/bin/env bash

# Exit on error
set -e

# Move to the script's directory
cd "$(dirname "$0")"

# Path to pipex
PIPEX_PATH="../pipex"

# Create the input file
cat > infile.txt <<EOF
Hive Helsinki is a new kind of coding school that gives you a fast-track path to a future-proofed career.
There are no teachers, lectures, or books at Hive.
Instead, you learn coding together with other students and work on practical, real-life projects.
No previous education, coding experience or qualifications are required and tuition is completely free!
EOF

# Remove old output files
rm -f output*.txt

# Define tests using a '|' delimiter for easy parsing:
tests=(
"infile.txt|grep Hive|wc -l|output1.txt|Count the number of lines containing 'Hive'"
"infile.txt|cat|sort|output2.txt|Sort all lines alphabetically"
"infile.txt|grep coding|tr a-z A-Z|output3.txt|Extract lines with 'coding' and uppercase them"
"infile.txt|cat|wc -w|output4.txt|Count total number of words"
"infile.txt|cat|head -n 2|output5.txt|Show the first two lines"
"infile.txt|grep -v Hive|wc -l|output6.txt|Count lines that do not contain 'Hive'"
"infile.txt|tail -n 1|tr a-z A-Z|output7.txt|Last line in uppercase"
"infile.txt|grep -i free|wc -l|output8.txt|Count lines containing 'free' (case-insensitive)"
"infile.txt|grep you|wc -w|output9.txt|Count the number of words in lines containing 'you'"
"infile.txt|cat|wc|output10.txt|Show line, word, and character counts"
)

i=1
for test in "${tests[@]}"; do
    # Parse the test line into variables
    IFS='|' read -r infile cmd1 cmd2 outfile description <<< "$test"

    echo "Test $i: $description"
    echo "$PIPEX_PATH \"$infile\" \"$cmd1\" \"$cmd2\" \"$outfile\""
    $PIPEX_PATH "$infile" "$cmd1" "$cmd2" "$outfile"

    if [ -f "$outfile" ]; then
        echo "Output written to $outfile:"
        cat "$outfile"
        echo
    else
        echo "No output file produced!"
        echo
    fi
    i=$((i+1))
done

echo "All tests completed. Check the output files (output1.txt, output2.txt, etc.) for results."
