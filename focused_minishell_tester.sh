#!/bin/bash

# Focused Minishell Tester - Following standard patterns
# Simplified and accurate testing approach

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Configuration
MINISHELL="./minishell"
TEST_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0

# Results tracking
declare -a FAILED_TESTS=()

print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE} $1${NC}"
    echo -e "${BLUE}================================${NC}"
}

test_command() {
    local description="$1"
    local command="$2"
    local expected_output="$3"
    
    ((TEST_COUNT++))
    
    # Run the command in minishell
    local output
    output=$(echo -e "$command\nexit" | timeout 5s $MINISHELL 2>&1 | grep -v "👉\|victor\|exit" | sed '/^$/d')
    
    # Check result
    if [[ "$output" == "$expected_output" ]] || [[ -z "$output" && -z "$expected_output" ]]; then
        echo -e "Test $TEST_COUNT: $description ${GREEN}✅ PASS${NC}"
        ((PASS_COUNT++))
    else
        echo -e "Test $TEST_COUNT: $description ${RED}❌ FAIL${NC}"
        echo -e "  Expected: '$expected_output'"
        echo -e "  Got:      '$output'"
        ((FAIL_COUNT++))
        FAILED_TESTS+=("Test $TEST_COUNT: $description")
    fi
}

# Check if minishell exists
if [[ ! -f "$MINISHELL" ]]; then
    echo -e "${RED}Error: $MINISHELL not found${NC}"
    exit 1
fi

print_header "MINISHELL TESTER"
echo "Testing: $MINISHELL"
echo

# Basic Echo Tests
print_header "ECHO TESTS"
test_command "echo hello" "echo hello" "hello"
test_command "echo multiple words" "echo hello world" "hello world" 
test_command "echo empty" "echo" ""
test_command "echo with quotes" "echo 'hello world'" "hello world"

# Environment Variables
print_header "ENVIRONMENT VARIABLES"
test_command "echo USER" "echo \$USER" "$USER"
test_command "echo undefined var" "echo \$UNDEFINED_VAR" ""
test_command "export and echo" $'export TEST=hello\necho $TEST' "hello"

# Builtin Commands
print_header "BUILTIN COMMANDS"
test_command "pwd" "pwd" "$(pwd)"
test_command "cd and pwd" $'cd /\npwd' "/"

# Pipes
print_header "PIPE TESTS"
test_command "echo pipe cat" "echo hello | cat" "hello"
test_command "multiple pipes" "echo hello | cat | cat" "hello"

# Redirections 
print_header "REDIRECTION TESTS"
test_command "redirect output" $'echo test > output.txt\ncat output.txt' "test"
test_command "redirect input" $'echo input_content > input.txt\ncat < input.txt' "input_content"

# Error Handling
print_header "ERROR HANDLING"
# Note: These will test error messages, but we focus on basic functionality

# File Descriptor Redirection (our recent fix)
print_header "FILE DESCRIPTOR REDIRECTION"
test_command "stderr redirect" "ls /nonexistent 2>&1 | grep 'cannot access'" "ls: cannot access '/nonexistent': No such file or directory"

# Results Summary
echo
print_header "RESULTS"
echo -e "Total Tests: $TEST_COUNT"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"

if [[ $FAIL_COUNT -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit_code=0
else
    echo -e "${RED}Failed Tests:${NC}"
    for test in "${FAILED_TESTS[@]}"; do
        echo -e "  ${RED}- $test${NC}"
    done
    exit_code=1
fi

# Cleanup
rm -f output.txt input.txt

echo -e "Success Rate: $((PASS_COUNT * 100 / TEST_COUNT))%"
exit $exit_code
