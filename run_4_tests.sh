#!/bin/bash

# Run 4 tests
echo "##########################################"
echo "### --------- Running 4 Tests -------- ###"
echo "##########################################"
echo ""

sleep 0.5

# Function to run each test
run_test() {
  local test_name=$1
  local test_directory=$2
  local command=$3

  echo "Running $test_name..."
  cd "$test_directory" || { echo "Error: Failed to change directory to $test_directory"; exit 1; }
  eval "$command"  # Use eval to ensure the full command string is executed
  local exit_code=$?
  cd ..
  echo ""
  sleep 0.5

  if [ $exit_code -ne 0 ]; then
    echo "Error: $test_name failed with exit code $exit_code."
    exit $exit_code
  fi
}

# Run Test 1
run_test "Test 1" "1_tester" "bash run.sh"

# Run Test 2
run_test "Test 2" "2_tester" "./run.sh"

# Run Test 3
run_test "Test 3" "3_tester" "bash pipex_tester.sh m"

# Run Test 4
run_test "Test 4" "4_tester" "make"

echo "##########################################"
echo "### ----- All 4 Tests Completed ------ ###"
echo "##########################################"
