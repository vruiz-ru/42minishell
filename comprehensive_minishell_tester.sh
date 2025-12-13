#!/bin/bash

# Comprehensive Minishell Tester
# Based on standard minishell_tester patterns with extensive test coverage

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
NC='\033[0m' # No Color

# Configuration
MINISHELL_PATH="./minishell"
BASH_CMD="/bin/bash"
TIMEOUT_DURATION=5
TEST_COUNT=0
PASSED_COUNT=0
FAILED_COUNT=0
ERROR_FILE="tester_errors.txt"

# Create/clear error file
> "$ERROR_FILE"

# Helper functions
print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}"
}

print_test() {
    echo -e "${YELLOW}Test $TEST_COUNT: $1${NC}"
}

run_test() {
    local test_name="$1"
    local command="$2"
    
    ((TEST_COUNT++))
    print_test "$test_name"
    
    # Create temporary files for comparison
    local mini_input="/tmp/minishell_test_input"
    local mini_output="/tmp/minishell_test_output"
    local bash_input="/tmp/bash_test_input"
    local bash_output="/tmp/bash_test_output"
    
    # Prepare input files
    echo -e "$command\nexit" > "$mini_input"
    echo -e "$command" > "$bash_input"
    
    # Run minishell
    timeout $TIMEOUT_DURATION $MINISHELL_PATH < "$mini_input" > "$mini_output" 2>&1
    local mini_exit_code=$?
    
    # Run bash
    timeout $TIMEOUT_DURATION $BASH_CMD --posix < "$bash_input" > "$bash_output" 2>&1
    local bash_exit_code=$?
    
    # Get outputs (remove prompt lines and clean up for comparison)
    local mini_result=$(grep -v "👉\|>.*victor\|minishell:" "$mini_output" 2>/dev/null | sed '/^exit$/d' | sed '/^$/d' | head -20)
    local bash_result=$(cat "$bash_output" 2>/dev/null | sed '/^$/d' | head -20)
    
    # Compare results (normalize whitespace for comparison)
    local mini_normalized=$(echo "$mini_result" | tr -d '\r' | sort)
    local bash_normalized=$(echo "$bash_result" | tr -d '\r' | sort)
    
    if [[ "$mini_normalized" == "$bash_normalized" ]] || [[ -z "$mini_result" && -z "$bash_result" ]]; then
        echo -e "   ${GREEN}✅ PASSED${NC}"
        ((PASSED_COUNT++))
    else
        echo -e "   ${RED}❌ FAILED${NC}"
        ((FAILED_COUNT++))
        
        # Log error details
        {
            echo "TEST $TEST_COUNT: $test_name"
            echo "Command: $command"
            echo "Minishell exit code: $mini_exit_code"
            echo "Bash exit code: $bash_exit_code"
            echo "Minishell output:"
            cat "$mini_output"
            echo "Bash output:"
            cat "$bash_output"
            echo "---"
            echo
        } >> "$ERROR_FILE"
    fi
    
    # Cleanup
    rm -f "$mini_input" "$mini_output" "$bash_input" "$bash_output"
}

# Test setup
print_header "COMPREHENSIVE MINISHELL TESTER"
echo -e "${CYAN}Testing minishell: $MINISHELL_PATH${NC}"
echo -e "${CYAN}Reference bash: $BASH_CMD${NC}"
echo

# Check if minishell exists
if [[ ! -f "$MINISHELL_PATH" ]]; then
    echo -e "${RED}Error: Minishell executable not found at $MINISHELL_PATH${NC}"
    exit 1
fi

# Compile check
print_header "COMPILATION CHECK"
if make -n 2>&1 | grep -q "\-Wall.*\-Wextra.*\-Werror\|--Werror.*\-Wall.*\-Wextra\|\-Wextra.*\-Wall.*\-Werror"; then
    echo -e "${GREEN}✅ Makefile includes required flags (-Wall -Wextra -Werror)${NC}"
else
    echo -e "${RED}❌ Makefile missing required compilation flags${NC}"
fi

make > /dev/null 2>&1
if make 2>&1 | grep -q "Nothing to be done\|up to date"; then
    echo -e "${GREEN}✅ Project compiles successfully${NC}"
else
    echo -e "${RED}❌ Compilation errors detected${NC}"
fi
echo

# ================================
# 1. BASIC COMMANDS
# ================================
print_header "1. BASIC COMMANDS"

run_test "Simple echo" "echo hello"
run_test "Echo with multiple args" "echo hello world test"
run_test "Echo empty" "echo"
run_test "Echo with spaces" "echo 'hello world'"
run_test "pwd command" "pwd"
run_test "ls current directory" "ls"
run_test "ls with flags" "ls -la"
run_test "cat with existing file" "cat /etc/passwd"
run_test "date command" "date"
run_test "whoami command" "whoami"

# ================================
# 2. BUILTIN COMMANDS
# ================================
print_header "2. BUILTIN COMMANDS"

run_test "env command" "env"
run_test "export new variable" "export TEST_VAR=hello"
run_test "echo exported variable" "echo \$TEST_VAR"
run_test "unset variable" "unset TEST_VAR"
run_test "echo unset variable" "echo \$TEST_VAR"
run_test "export without value" "export EMPTY_VAR"
run_test "export multiple" "export VAR1=value1 VAR2=value2"
run_test "cd to root" "cd /"
run_test "pwd after cd" "pwd"
run_test "cd back home" "cd"
run_test "cd to non-existent" "cd /nonexistent_directory_12345"

# ================================
# 3. ECHO BUILTIN TESTS  
# ================================
print_header "3. ECHO BUILTIN TESTS"

run_test "echo -n flag" "echo -n hello"
run_test "echo -n with newline" "echo -n hello; echo world"
run_test "echo multiple -n" "echo -n -n hello"
run_test "echo invalid flag" "echo -x hello"
run_test "echo with quotes" "echo \"hello world\""
run_test "echo with single quotes" "echo 'hello world'"
run_test "echo escaped characters" "echo hello\\nworld"
run_test "echo with \$" "echo \$USER"

# ================================
# 4. ENVIRONMENT VARIABLES
# ================================
print_header "4. ENVIRONMENT VARIABLES"

run_test "Echo USER variable" "echo \$USER"
run_test "Echo HOME variable" "echo \$HOME"
run_test "Echo PATH variable" "echo \$PATH"
run_test "Echo undefined variable" "echo \$UNDEFINED_VAR_12345"
run_test "Exit status variable" "echo \$?"
run_test "Variable in double quotes" "echo \"\$USER\""
run_test "Variable in single quotes" "echo '\$USER'"
run_test "Multiple variables" "echo \$USER \$HOME"
run_test "Variable concatenation" "echo \$USER_suffix"
run_test "Complex variable usage" "echo prefix\$USER suffix"

# ================================
# 5. QUOTES AND ESCAPING
# ================================
print_header "5. QUOTES AND ESCAPING"

run_test "Single quotes" "echo 'hello world'"
run_test "Double quotes" "echo \"hello world\""
run_test "Mixed quotes" "echo 'hello \"world\"'"
run_test "Nested quotes" "echo \"hello 'world'\""
run_test "Variable in quotes" "echo \"Hello \$USER\""
run_test "No expansion in single quotes" "echo '\$USER'"
run_test "Empty quotes" "echo '' \"\""
run_test "Quotes with spaces" "echo \"  hello    world  \""
run_test "Escape characters" "echo \\\"hello\\\""
run_test "Backslash escaping" "echo \\\$USER"

# ================================
# 6. PIPES
# ================================
print_header "6. PIPES"

run_test "Simple pipe" "echo hello | cat"
run_test "Multiple pipes" "echo hello | cat | cat"
run_test "ls pipe to grep" "ls | grep minishell"
run_test "env pipe to grep" "env | grep USER"
run_test "echo pipe to wc" "echo hello world | wc -w"
run_test "cat pipe to head" "cat /etc/passwd | head -5"
run_test "Multiple commands pipe" "echo test; echo hello | cat"
run_test "Pipe with builtin" "echo \$USER | cat"
run_test "Complex pipe chain" "echo hello world | cat | grep hello"
run_test "Pipe with quotes" "echo 'hello world' | cat"

# ================================
# 7. REDIRECTIONS
# ================================
print_header "7. REDIRECTIONS"

# Setup test files
echo "test input content" > test_input.txt
echo "existing content" > test_existing.txt

run_test "Input redirection" "cat < test_input.txt"
run_test "Output redirection" "echo 'test output' > test_out.txt"
run_test "Check output file" "cat test_out.txt"
run_test "Append redirection 1" "echo 'line1' > test_append.txt"
run_test "Append redirection 2" "echo 'line2' >> test_append.txt"
run_test "Check append result" "cat test_append.txt"
run_test "Multiple redirections" "cat < test_input.txt > test_copy.txt"
run_test "Overwrite existing file" "echo 'new content' > test_existing.txt"
run_test "Redirection with pipes" "echo hello | cat > pipe_output.txt"
run_test "File descriptor redirection" "ls /nonexistent 2>&1"

# ================================
# 8. HEREDOC
# ================================
print_header "8. HEREDOC"

run_test "Simple heredoc" "cat << EOF
hello
world
EOF"

run_test "Heredoc with variables" "cat << EOF
User: \$USER
Home: \$HOME
EOF"

run_test "Quoted heredoc delimiter" "cat << 'END'
\$USER will not expand
END"

run_test "Heredoc to file" "cat << EOF > heredoc_output.txt
heredoc content
EOF"

# ================================
# 9. ERROR HANDLING
# ================================
print_header "9. ERROR HANDLING"

run_test "Command not found" "nonexistent_command_12345"
run_test "Invalid option" "ls --invalid-option-12345"
run_test "Permission denied" "cat /root/.bashrc"
run_test "Directory as command" "/tmp"
run_test "File not found" "cat /nonexistent_file_12345.txt"
run_test "Pipe with error" "nonexistent_cmd | cat"
run_test "Redirection error" "cat < /nonexistent_input_file.txt"
run_test "Multiple errors" "nonexistent1 | nonexistent2"
run_test "Syntax error - unclosed quote" "echo 'unclosed"
run_test "Empty command" ""

# ================================
# 10. EXIT STATUS
# ================================
print_header "10. EXIT STATUS"

run_test "Success command status" "/bin/true; echo \$?"
run_test "Failure command status" "/bin/false; echo \$?"
run_test "Command not found status" "nonexistent_cmd_xyz; echo \$?"
run_test "Builtin success status" "echo hello; echo \$?"
run_test "Pipe exit status" "echo hello | cat; echo \$?"
run_test "Last command in pipe" "/bin/false | /bin/true; echo \$?"
run_test "Exit status after cd success" "cd /; echo \$?"
run_test "Exit status after cd failure" "cd /nonexistent; echo \$?"

# ================================
# 11. COMPLEX SCENARIOS
# ================================
print_header "11. COMPLEX SCENARIOS"

run_test "Multiple commands" "echo hello; echo world"
run_test "Commands with variables" "export X=test; echo \$X; unset X"
run_test "Pipes and redirections" "echo hello | cat > complex_output.txt"
run_test "Variable expansion in quotes" "export MSG='hello world'; echo \"\$MSG\""
run_test "Complex pipe chain" "echo 'line1\nline2\nline3' | grep line | wc -l"
run_test "Redirection with variables" "echo \$USER > user_output.txt"
run_test "Mixed quotes and variables" "echo 'User: '\$USER' Home: '\$HOME"
run_test "Command substitution-like" "echo \$(echo hello)"
run_test "Nested command execution" "echo test | cat | cat | grep test"
run_test "Error in pipe chain" "nonexistent_cmd | cat | grep hello"

# ================================
# 12. STRESS TESTS
# ================================
print_header "12. STRESS TESTS"

run_test "Very long command line" "echo $(printf 'a%.0s' {1..100})"
run_test "Many pipes" "echo hello | cat | cat | cat | cat | cat"
run_test "Multiple redirections" "echo test > out1.txt > out2.txt"
run_test "Large heredoc" "cat << LARGE
$(for i in {1..50}; do echo line$i; done)
LARGE"
run_test "Many variables" "export A=1 B=2 C=3 D=4 E=5; echo \$A\$B\$C\$D\$E"

# ================================
# RESULTS SUMMARY
# ================================
echo
print_header "TEST RESULTS SUMMARY"

echo -e "${CYAN}Total tests: $TEST_COUNT${NC}"
echo -e "${GREEN}Passed: $PASSED_COUNT${NC}"
echo -e "${RED}Failed: $FAILED_COUNT${NC}"

if [[ $FAILED_COUNT -eq 0 ]]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit_code=0
else
    echo -e "${RED}❌ Some tests failed. Check $ERROR_FILE for details.${NC}"
    echo -e "${YELLOW}Failure rate: $(( FAILED_COUNT * 100 / TEST_COUNT ))%${NC}"
    exit_code=1
fi

# Performance info
echo
echo -e "${PURPLE}Performance Summary:${NC}"
echo -e "${PURPLE}- Average test time: ~${TIMEOUT_DURATION}s max per test${NC}"
echo -e "${PURPLE}- Error details saved to: $ERROR_FILE${NC}"

# Memory leak check (if valgrind is available)
if command -v valgrind >/dev/null 2>&1; then
    echo
    print_header "MEMORY LEAK CHECK"
    echo -e "Running basic memory leak test..."
    echo -e "echo hello\nexit" | timeout 10s valgrind --leak-check=summary --suppressions=readline.supp $MINISHELL_PATH 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost" || echo -e "${GREEN}No significant leaks detected${NC}"
fi

# Cleanup test files
echo
echo -e "${CYAN}Cleaning up test files...${NC}"
rm -f test_input.txt test_out.txt test_append.txt test_copy.txt test_existing.txt
rm -f heredoc_output.txt complex_output.txt user_output.txt out1.txt out2.txt
rm -f pipe_output.txt

echo -e "${GREEN}Testing complete!${NC}"
exit $exit_code
