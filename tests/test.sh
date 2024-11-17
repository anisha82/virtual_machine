#!/bin/bash

# Function to run a test case
run_test() {
    test_name=$1
    bytecode=$2
    expected_output=$3

    echo "Running Test: $test_name"
    echo $bytecode > program.vm  # Save bytecode to a file
    output=$(docker run --rm -v $(pwd):/app virtual-machine ./virtual_machine program.vm)

    if [[ "$output" == "$expected_output" ]]; then
        echo "✅ $test_name PASSED"
    else
        echo "❌ $test_name FAILED"
        echo "Expected: $expected_output"
        echo "Got: $output"
    fi
}

# Add test cases
run_test "Addition" "1 5 2 10 3 6" "Output: 15"
run_test "Subtraction" "1 10 2 5 4 6" "Output: 5"
run_test "Multiplication" "1 7 2 3 5 6" "Output: 21"
run_test "Division" "1 20 2 4 6 6" "Output: 5"
run_test "Bitwise AND" "1 12 2 10 7 6" "Output: 8"

# Clean up
rm -f program.vm