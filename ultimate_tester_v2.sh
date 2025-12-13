#!/bin/bash

# Ultimate Minishell Tester v2.0
# Clean and comprehensive test suite

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# Configuration
MINISHELL="./minishell"
BASH="/bin/bash"
TIMEOUT=3
TEST_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0

print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE} $1${NC}"  
    echo -e "${BLUE}================================${NC}"
}

run_test() {
    local description="$1"
    local command="$2"
    
    ((TEST_COUNT++))
    
    # Run minishell test
    local mini_output
    mini_output=$(echo -e "$command\nexit" | timeout $TIMEOUT $MINISHELL 2>&1 | grep -v "👉\|~/victor\|exit" | sed '/^$/d')
    
    # Run bash test  
    local bash_output
    bash_output=$(echo "$command" | timeout $TIMEOUT $BASH 2>&1)
    
    # Compare (basic comparison, can be enhanced)
    if [[ "$mini_output" == "$bash_output" ]] || [[ -z "$mini_output" && -z "$bash_output" ]]; then
        echo -e "Test $TEST_COUNT: $description ${GREEN}✅ PASS${NC}"
        ((PASS_COUNT++))
    else
        echo -e "Test $TEST_COUNT: $description ${RED}❌ FAIL${NC}"
        ((FAIL_COUNT++))
    fi
}

# Verify minishell exists
if [[ ! -f "$MINISHELL" ]]; then
    echo -e "${RED}❌ Minishell not found: $MINISHELL${NC}"
    exit 1
fi

print_header "ULTIMATE MINISHELL TESTER"
echo -e "${CYAN}Testing: $MINISHELL${NC}"
echo

# ================================
# BASIC COMMANDS
# ================================
print_header "BASIC COMMANDS"
run_test "Simple echo" "echo hello"
run_test "Echo multiple" "echo hello world" 
run_test "Echo empty" "echo"
run_test "PWD command" "pwd"
run_test "LS command" "ls"

# ================================  
# BUILTIN COMMANDS
# ================================
print_header "BUILTIN COMMANDS"
run_test "Export variable" "export TEST=hello"
run_test "Echo exported" 'export TEST=hello; echo $TEST'
run_test "CD root" "cd /"
run_test "CD home" "cd"

# ================================
# ENVIRONMENT VARIABLES  
# ================================
print_header "ENVIRONMENT VARIABLES"
run_test "USER variable" 'echo $USER'
run_test "HOME variable" 'echo $HOME' 
run_test "Undefined var" 'echo $UNDEFINED'
run_test "Exit status" 'echo $?'

# ================================
# PIPES
# ================================  
print_header "PIPES"
run_test "Simple pipe" "echo hello | cat"
run_test "Multiple pipes" "echo hello | cat | cat"
run_test "Pipe with grep" "echo hello world | grep hello"

# ================================
# REDIRECTIONS
# ================================
print_header "REDIRECTIONS"

# Setup test file
echo "test content" > test_input.txt

run_test "Input redirect" "cat < test_input.txt"
run_test "Output redirect" 'echo output > test_out.txt; cat test_out.txt'
run_test "Append redirect" 'echo line1 > test.txt; echo line2 >> test.txt; cat test.txt'

# ================================
# FILE DESCRIPTOR REDIRECTION
# ================================  
print_header "FD REDIRECTION"
run_test "Stderr to stdout" "ls /nonexistent 2>&1 | grep cannot"

# ================================
# ERROR HANDLING
# ================================
print_header "ERROR HANDLING"  
run_test "Command not found" "nonexistent_cmd"
run_test "File not found" "cat nonexistent.txt"

# ================================
# RESULTS
# ================================
echo
print_header "TEST RESULTS"
echo -e "${CYAN}Total Tests: $TEST_COUNT${NC}"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"

success_rate=$((PASS_COUNT * 100 / TEST_COUNT))
echo -e "${PURPLE}Success Rate: ${success_rate}%${NC}"

if [[ $FAIL_COUNT -eq 0 ]]; then
    echo -e "${GREEN}🎉 PERFECT SCORE! 🎉${NC}"
else
    echo -e "${YELLOW}Some tests failed - check implementation${NC}"
fi

# Cleanup
rm -f test_input.txt test_out.txt test.txt

echo -e "${BLUE}Testing Complete!${NC}"
