#!/bin/bash

# Ultimate Minishell Tester
# Comprehensive test suite with accurate result comparison

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
TIMEOUT=5
TEST_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0
ERROR_FILE="ultimate_tester_errors.txt"

# Clear error file
> "$ERROR_FILE"

print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE} $1${NC}"  
    echo -e "${BLUE}================================${NC}"
}

run_minishell_test() {
    local cmd="$1"
    echo -e "$cmd\nexit" | timeout $TIMEOUT $MINISHELL 2>&1 | \
        grep -v "👉\|~/victor\|>.*victor\|^exit$" | \
        sed '/^$/d' | \
        head -50
}

run_bash_test() {
    local cmd="$1"
    echo "$cmd" | timeout $TIMEOUT $BASH --posix 2>&1 | head -50
}

test_command() {
    local description="$1" 
    local command="$2"
    
    ((TEST_COUNT++))
    
    local mini_out=$(run_minishell_test "$command")
    local bash_out=$(run_bash_test "$command") 
    
    # Normalize outputs for comparison
    local mini_clean=$(echo "$mini_out" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | sort)
    local bash_clean=$(echo "$bash_out" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | sort)
    
    if [[ "$mini_clean" == "$bash_clean" ]]; then
        echo -e "Test $TEST_COUNT: $description ${GREEN}✅ PASS${NC}"
        ((PASS_COUNT++))
    else
        echo -e "Test $TEST_COUNT: $description ${RED}❌ FAIL${NC}"
        ((FAIL_COUNT++))
        
        # Log detailed error
        {
            echo "=== TEST $TEST_COUNT FAILED: $description ==="
            echo "Command: $command"
            echo "--- Minishell Output ---"
            echo "$mini_out"
            echo "--- Bash Output ---" 
            echo "$bash_out"
            echo "--- Comparison ---"
            echo "Mini (normalized): $mini_clean"
            echo "Bash (normalized): $bash_clean"
            echo
        } >> "$ERROR_FILE"
    fi
}

# Verify minishell exists
if [[ ! -f "$MINISHELL" ]]; then
    echo -e "${RED}❌ Minishell not found: $MINISHELL${NC}"
    exit 1
fi

print_header "ULTIMATE MINISHELL TESTER"
echo -e "${CYAN}Minishell: $MINISHELL${NC}"
echo -e "${CYAN}Reference: $BASH${NC}"
echo

# ================================
# BASIC FUNCTIONALITY
# ================================
print_header "BASIC COMMANDS"
test_command "Simple echo" "echo hello"
test_command "Echo multiple args" "echo hello world test"
test_command "Echo empty" "echo"
test_command "Echo with spaces" "echo 'hello    world'"
test_command "PWD command" "pwd"
test_command "LS command" "ls"
test_command "Cat existing file" "cat /etc/passwd"
test_command "Date command" "date"
test_command "Whoami command" "whoami"

# ================================
# BUILTIN COMMANDS  
# ================================
print_header "BUILTIN COMMANDS"
test_command "Env command" "env"
test_command "Export variable" "export TEST_VAR=hello"
test_command "Echo exported var" $'export TEST_VAR=hello\necho $TEST_VAR'
test_command "Unset variable" $'export TEST_VAR=hello\nunset TEST_VAR\necho $TEST_VAR'
test_command "CD to root" "cd /"
test_command "CD back home" "cd"
test_command "CD invalid directory" "cd /nonexistent_dir_12345"

# ================================
# ECHO BUILTIN
# ================================  
print_header "ECHO BUILTIN"
test_command "Echo -n flag" "echo -n hello"
test_command "Echo invalid flag" "echo -x hello"
test_command "Echo with quotes" 'echo "hello world"'
test_command "Echo single quotes" "echo 'hello world'"

# ================================
# ENVIRONMENT VARIABLES
# ================================
print_header "ENVIRONMENT VARIABLES"  
test_command "USER variable" "echo \$USER"
test_command "HOME variable" "echo \$HOME"
test_command "PATH variable" "echo \$PATH"
test_command "Undefined variable" "echo \$UNDEFINED_VAR_XYZ"
test_command "Exit status \$?" "echo \$?"
test_command "Variable in quotes" 'echo "$USER"'
test_command "Variable no expansion" 'echo '\''$USER'\'''

# ================================
# QUOTES AND ESCAPING
# ================================
print_header "QUOTES AND ESCAPING"
test_command "Single quotes" "echo 'hello world'"
test_command "Double quotes" 'echo "hello world"'
test_command "Mixed quotes" 'echo '\''hello "world"'\'''
test_command "Variable expansion" 'echo "User: $USER"'
test_command "No expansion single" 'echo '\''$USER'\'''
test_command "Empty quotes" 'echo "" '\''''\''''

# ================================
# PIPES
# ================================
print_header "PIPES"
test_command "Simple pipe" "echo hello | cat"  
test_command "Multiple pipes" "echo hello | cat | cat"
test_command "Env pipe grep" "env | grep USER"
test_command "Echo pipe wc" "echo hello world | wc -w"
test_command "Pipe with builtin" "echo \$USER | cat"

# ================================  
# REDIRECTIONS
# ================================
print_header "REDIRECTIONS"
# Setup test files
echo "test input" > test_input.txt

test_command "Input redirection" "cat < test_input.txt"
test_command "Output redirection" $'echo "test output" > test_out.txt\ncat test_out.txt'
test_command "Append redirection" $'echo "line1" > test_append.txt\necho "line2" >> test_append.txt\ncat test_append.txt'
test_command "Multiple redirections" "cat < test_input.txt > test_copy.txt && cat test_copy.txt"

# ================================
# FILE DESCRIPTOR REDIRECTIONS  
# ================================
print_header "FILE DESCRIPTOR REDIRECTION"
test_command "Stderr to stdout" "ls /nonexistent 2>&1 | grep 'cannot access'"
test_command "Stderr redirect 2>" "ls /nonexistent 2>/dev/null"

# ================================
# HEREDOC
# ================================
print_header "HEREDOC"
test_command "Simple heredoc" $'cat << EOF\nhello\nworld\nEOF'
test_command "Heredoc with vars" $'cat << EOF\nUser: $USER\nEOF'

# ================================
# ERROR HANDLING
# ================================
print_header "ERROR HANDLING"
test_command "Command not found" "nonexistent_command_xyz"
test_command "Permission denied" "cat /root/.ssh/id_rsa 2>/dev/null || echo 'permission denied'"
test_command "File not found" "cat nonexistent_file.txt"

# ================================
# COMPLEX SCENARIOS
# ================================
print_header "COMPLEX SCENARIOS"
test_command "Multiple commands" $'echo hello\necho world'
test_command "Export and use" $'export X=test\necho $X'
test_command "Pipe and redirect" "echo hello | cat > complex_out.txt && cat complex_out.txt"
test_command "Variable in quotes" $'export MSG="hello world"\necho "$MSG"'

# ================================
# RESULTS SUMMARY
# ================================
echo
print_header "TEST RESULTS"
echo -e "${CYAN}Total Tests: $TEST_COUNT${NC}"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"  
echo -e "${RED}Failed: $FAIL_COUNT${NC}"

success_rate=$((PASS_COUNT * 100 / TEST_COUNT))
echo -e "${PURPLE}Success Rate: ${success_rate}%${NC}"

if [[ $FAIL_COUNT -eq 0 ]]; then
    echo -e "${GREEN}🎉 PERFECT SCORE! ALL TESTS PASSED! 🎉${NC}"
    exit_code=0
else
    echo -e "${YELLOW}Check detailed errors in: $ERROR_FILE${NC}"
    exit_code=1
fi

# Memory check
if command -v valgrind >/dev/null 2>&1; then
    echo
    print_header "MEMORY CHECK"
    echo "Running memory leak test..."
    leak_output=$(echo -e "echo test\nexit" | valgrind --leak-check=summary --suppressions=readline.supp $MINISHELL 2>&1 | grep -E "definitely lost|indirectly lost")
    if [[ -z "$leak_output" ]]; then
        echo -e "${GREEN}✅ No memory leaks detected${NC}"
    else
        echo -e "${RED}⚠️  Potential leaks detected${NC}"
    fi
fi

# Cleanup
rm -f test_input.txt test_out.txt test_append.txt test_copy.txt complex_out.txt

echo -e "${BLUE}Testing complete!${NC}"
exit $exit_code
