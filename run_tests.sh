#!/bin/bash

# Test Cases for the Pipex Program

echo "Running Pipex Tests..."
echo ""
echo "Creating dir and files for tests..."

sleep 0.5

#Create test dir and test files
mkdir -p test_files
touch test_files/empty.txt
chmod 777 test_files/empty.txt
touch test_files/existing.txt

# Fill 'existing.txt' with content
cat << EOF > test_files/existing.txt
Line 1
Line 2
Line 3 Last line
EOF

chmod 777 test_files/existing.txt
touch test_files/noread.txt
chmod u-r test_files/noread.txt
touch test_files/nowrite.txt
chmod u-w test_files/nowrite.txt
echo ""


# Test Case 1: Non-existent Infile
echo "--------- 1: Non-existent Infile ---------"
echo ""
echo "INPUT COMMAND: < test_files/nonexistent.txt | ls > test_files/output.txt"
echo ""

< test_files/nonexistent.txt | ls > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/nonexistent.txt "cat" "ls" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 2: Non-existent Outfile
echo "--------- 2: Non-existent Outfile ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt cat | head -n 1 > test_files/nonexistent_output.txt"
echo ""

< test_files/existing.txt cat | head -n 1 > test_files/nonexistent_output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "head -n 1" test_files/nonexistent_output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 3: No Read Permission on Infile
echo "--------- 3: No Read Permission on Infile ---------"
echo ""
echo "INPUT COMMAND: < test_files/noread.txt cat | ls -l > test_files/output.txt"
echo ""

< test_files/noread.txt cat | ls -l > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/noread.txt "cat" "ls -l" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
chmod +r test_files/noread.txt
echo ""
sleep 0.5

# Test Case 4: No Write Permission on Outfile
echo "--------- 4: No Write Permission on Outfile ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt cat | > test_files/nowrite.txt"
echo ""

< test_files/existing.txt cat | > test_files/nowrite.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "cat" test_files/nowrite.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
chmod +w test_files/nowrite.txt
echo ""
sleep 0.5

# Test Case 5: Not Empty Infile
echo "--------- 5: Not Empty Infile ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt cat | > test_files/output.txt"
echo ""

< test_files/existing.txt cat | > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 6: First Command Not Found
echo "--------- 6: First Command Not Found ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt nonexistentcmd1 | cat > test_files/output.txt"
echo ""

< test_files/existing.txt nonexistentcmd1 | cat > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "nonexistentcmd1" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 7: Second Command Not Found
echo "--------- 7: Second Command Not Found ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt cat | nonexistentcmd2 > test_files/output.txt"
echo ""

< test_files/existing.txt cat | nonexistentcmd2 > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "nonexistentcmd2" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 8: Both Commands Not Found
echo "--------- 8: Both Commands Not Found ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt nonexistentcmd1 | nonexistentcmd2 > test_files/output.txt"
echo ""

TERMINAL_OUTPUT=$(< test_files/existing.txt nonexistentcmd1 | nonexistentcmd2 > test_files/output.txt >&1)
TERMINAL_EXIT_CODE=$?

# Print the captured terminal output
echo "$TERMINAL_OUTPUT"

# Print and execute the pipex command
echo "./pipex test_files/existing.txt \"nonexistentcmd1\" \"nonexistentcmd2\" test_files/output.txt"
./pipex test_files/existing.txt "nonexistentcmd1" "nonexistentcmd2" test_files/output.txt 2>&1
PIPEX_EXIT_CODE=$?

# Output the results
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 9: Empty First Command
echo "--------- 9: Empty First Command ---------"
echo ""
echo "INPUT COMMAND: ./pipex test_files/existing.txt "" "cat" test_files/output.txt"
echo ""

./pipex test_files/existing.txt "" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 10: Empty Second Command
echo "--------- 10: Empty Second Command ---------"
echo ""
echo "INPUT COMMAND: ./pipex test_files/existing.txt "cat" "" test_files/output.txt"
echo ""

./pipex test_files/existing.txt "cat" "" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 11: Empty Both Commands
echo "--------- 11: Empty Both Commands ---------"
echo ""
echo "INPUT COMMAND: ./pipex test_files/existing.txt "" "" test_files/output.txt"
echo ""

./pipex test_files/existing.txt "" "" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 12: Command Using Environment Variables
echo "--------- 12: Command Using Environment Variables ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt env | grep PATH > test_files/PATHoutput.txt"
echo ""

< test_files/existing.txt env | grep PATH > test_files/PATHoutput.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "env" "grep PATH" test_files/PATHoutput.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 13: Broken Pipe Handling
echo "--------- 13: Broken Pipe Handling ---------"
echo ""
echo "INPUT COMMAND: yes | head -n 2 > test_files/YESoutput.txt"
echo ""

yes | head -n 2 > test_files/YESoutput.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "yes" "head -n 2" test_files/YESoutput.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 14: Command Producing No Output
echo "--------- 14: Command Producing No Output ---------"
echo ""
echo "INPUT COMMAND: < test_files/existing.txt grep "nonexistentpattern" | > test_files/output.txt"
echo ""

< test_files/existing.txt grep "nonexistentpattern" | > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "grep nonexistentpattern" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 15: No Arguments
echo "--------- 15: No Arguments ---------"
echo ""
echo "INPUT COMMAND: ./pipex"
echo ""

./pipex
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""
sleep 0.5

# Test Case 16: Less then 5 Arguments
echo "--------- 16: Less then 5 Arguments ---------"
echo ""
echo "INPUT COMMAND: ./pipex test_files/existing.txt "cat" test_files/output.txt"
echo ""
./pipex test_files/existing.txt "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

echo "### ----- Pipex Tests Completed ------ ###"