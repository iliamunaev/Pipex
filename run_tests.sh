#!/bin/bash

# Test Cases for the Pipex Program

echo "Running Pipex Tests..."
echo ""

# Test Case 1: Non-existent Infile
echo "--------- 1: Non-existent Infile ---------"
echo ""

< test_files/nonexistent.txt | ls > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/nonexistent.txt "cat" "ls" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 2: Non-existent Outfile
echo "--------- 2: Non-existent Outfile ---------"
echo ""

 < test_files/existing.txt cat | head -n 1 > test_files/nonexistent_output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "head -n 1" test_files/nonexistent_output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 3: No Read Permission on Infile
echo "--------- 3: No Read Permission on Infile ---------"
echo ""

chmod -r test_files/noread.txt
< test_files/noread.txt cat | ls -l > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/noread.txt "cat" "ls -l" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
chmod +r test_files/noread.txt
echo ""

# Test Case 4: No Write Permission on Outfile
echo "--------- 4: No Write Permission on Outfile ---------"
echo ""

touch test_files/nowrite.txt && chmod -w test_files/nowrite.txt
< test_files/existing.txt cat | > test_files/nowrite.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "cat" test_files/nowrite.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
chmod +w test_files/nowrite.txt
echo ""

# Test Case 5: Not Empty Infile
echo "--------- 5: Not Empty Infile ---------"
echo ""

< test_files/existing.txt cat | > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 6: First Command Not Found
echo "--------- 6: First Command Not Found ---------"
echo ""

< test_files/existing.txt nonexistentcmd1 | cat > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "nonexistentcmd1" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 7: Second Command Not Found
echo "--------- 7: Second Command Not Found ---------"
echo ""

< test_files/existing.txt cat | nonexistentcmd2 > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "cat" "nonexistentcmd2" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""


# Test Case 8: Both Commands Not Found
echo "--------- 8: Both Commands Not Found ---------"
echo ""

< test_files/existing.txt nonexistentcmd1 | nonexistentcmd2 > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "nonexistentcmd1" "nonexistentcmd2" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 9: Empty First Command
echo "--------- 9: Empty First Command ---------"
echo ""

< test_files/existing.txt "" | cat > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 10: Empty Second Command
echo "--------- 10: Empty Second Command ---------"
echo ""

./pipex test_files/existing.txt "cat" "" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 11: Empty Both Commands
echo "--------- 11: Empty Both Commands ---------"
echo ""

./pipex test_files/existing.txt "" "" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 13: Command Using Environment Variables
echo "--------- 13: Command Using Environment Variables ---------"
echo ""

< test_files/existing.txt env | grep PATH > test_files/PATHoutput.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "env" "grep PATH" test_files/PATHoutput.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 14: Broken Pipe Handling
echo "--------- 14: Broken Pipe Handling ---------"
echo ""

yes | head -n 2 > test_files/YESoutput.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "yes" "head -n 2" test_files/YESoutput.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""

# Test Case 15: Command Producing No Output
echo "--------- 15: Command Producing No Output ---------"
echo ""

< test_files/existing.txt grep "nonexistentpattern" | > test_files/output.txt 2>/dev/null
TERMINAL_EXIT_CODE=$?
./pipex test_files/existing.txt "grep nonexistentpattern" "cat" test_files/output.txt
PIPEX_EXIT_CODE=$?
echo "Terminal Exit Code: $TERMINAL_EXIT_CODE"
echo "Pipex Exit Code:    $PIPEX_EXIT_CODE"
echo ""


echo "Pipex Tests Completed."
