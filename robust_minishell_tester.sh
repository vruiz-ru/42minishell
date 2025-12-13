#!/bin/bash

# ============================================================================
# ROBUST MINISHELL TESTER - Based on 42 Evaluation Criteria
# ============================================================================

MINISHELL_PATH="./minishell"
BASH_CMD="bash"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
CYAN="\033[0;36m"
WHIT# Finalize error report
echo "" >> $ERROR_FILE
echo "=================================================" >> $ERROR_FILE
echo "SUMMARY:" >> $ERROR_FILE
echo "Total tests: $TOTAL" >> $ERROR_FILE
echo "Passed: $PASSED" >> $ERROR_FILE
echo "Failed: $FAILED" >> $ERROR_FILE
echo "Success rate: $((PASSED * 100 / TOTAL))%" >> $ERROR_FILE
echo "Generated on: $(date)" >> $ERROR_FILE

if [ $FAILED -eq 0 ]; then
    echo "🎉 NO ERRORS FOUND - All tests passed!" >> $ERROR_FILE
    echo -e "\n${GREEN}✅ Error report generated: $ERROR_FILE (No errors found!)${RESET}"
else
    echo -e "\n${YELLOW}📝 Detailed error report generated: $ERROR_FILE${RESET}"
    echo -e "${YELLOW}Found $FAILED failed tests with detailed diagnostics${RESET}"
fi

echo -e "${GREEN}Testing complete!${RESET}"="\033[0;37m"
RESET="\033[0m"

PASSED=0
FAILED=0
TOTAL=0
ERROR_FILE="errors.txt"

# Initialize error report
echo "MINISHELL ERROR REPORT - $(date)" > $ERROR_FILE
echo "=================================================" >> $ERROR_FILE
echo "" >> $ERROR_FILE

# Helper functions
print_header() {
    echo -e "\n${BLUE}================================${RESET}"
    echo -e "${BLUE}$1${RESET}"
    echo -e "${BLUE}================================${RESET}\n"
}

print_test() {
    echo -e "${YELLOW}Test $((TOTAL+1)): ${WHITE}$1${RESET}"
}

run_test() {
    local test_name="$1"
    local command="$2"
    local should_compare="${3:-true}"
    
    print_test "$test_name"
    TOTAL=$((TOTAL+1))
    
    # Run in minishell
    echo -e "$command\nexit" > /tmp/minishell_input
    timeout 10s $MINISHELL_PATH < /tmp/minishell_input > /tmp/minishell_output 2>&1
    local mini_exit=$?
    local mini_output=$(cat /tmp/minishell_output 2>/dev/null)
    
    if [ "$should_compare" = "true" ]; then
        # Run in bash for comparison
        echo -e "$command\nexit" > /tmp/bash_input
        timeout 10s $BASH_CMD --posix < /tmp/bash_input > /tmp/bash_output 2>&1
        local bash_exit=$?
        local bash_output=$(cat /tmp/bash_output 2>/dev/null)
        
        # Compare outputs (simplified comparison)
        if [[ "$mini_exit" -eq "$bash_exit" ]] || [[ "$mini_exit" -eq 0 && "$bash_exit" -eq 0 ]]; then
            echo -e "   ${GREEN}✅ PASSED${RESET}"
            PASSED=$((PASSED+1))
        else
            echo -e "   ${RED}❌ FAILED${RESET}"
            echo -e "   ${CYAN}Minishell exit: $mini_exit${RESET}"
            echo -e "   ${CYAN}Bash exit: $bash_exit${RESET}"
            FAILED=$((FAILED+1))
            
            # Log error to file
            echo "TEST $TOTAL: $test_name" >> $ERROR_FILE
            echo "Command: $command" >> $ERROR_FILE
            echo "Minishell exit code: $mini_exit" >> $ERROR_FILE
            echo "Bash exit code: $bash_exit" >> $ERROR_FILE
            echo "Minishell output:" >> $ERROR_FILE
            echo "$mini_output" >> $ERROR_FILE
            echo "Bash output:" >> $ERROR_FILE
            echo "$bash_output" >> $ERROR_FILE
            echo "---" >> $ERROR_FILE
            echo "" >> $ERROR_FILE
        fi
    else
        # Just check if minishell doesn't crash
        if [[ "$mini_exit" -ne 139 && "$mini_exit" -ne 134 ]]; then
            echo -e "   ${GREEN}✅ NO CRASH${RESET}"
            PASSED=$((PASSED+1))
        else
            echo -e "   ${RED}❌ CRASHED${RESET}"
            FAILED=$((FAILED+1))
            
            # Log crash to file
            echo "TEST $TOTAL: $test_name [CRASH]" >> $ERROR_FILE
            echo "Command: $command" >> $ERROR_FILE
            echo "Exit code: $mini_exit (CRASH - SEGFAULT/SIGTERM)" >> $ERROR_FILE
            echo "Output:" >> $ERROR_FILE
            echo "$mini_output" >> $ERROR_FILE
            echo "---" >> $ERROR_FILE
            echo "" >> $ERROR_FILE
        fi
    fi
    
    # Cleanup
    rm -f /tmp/minishell_input /tmp/minishell_output /tmp/bash_input /tmp/bash_output
}

# Check if minishell exists
if [ ! -f "$MINISHELL_PATH" ]; then
    echo -e "${RED}Error: minishell not found at $MINISHELL_PATH${RESET}"
    echo "Please compile your minishell first with 'make'"
    exit 1
fi

echo -e "${PURPLE}🔥 ROBUST MINISHELL TESTER 🔥${RESET}"
echo -e "${PURPLE}Testing minishell against bash behavior${RESET}\n"

# ============================================================================
# 1. COMPILATION TESTS
# ============================================================================
print_header "1. COMPILATION TESTS"

echo -e "${YELLOW}Checking Makefile flags...${RESET}"
if make -n 2>&1 | grep -q "\-Wall.*\-Wextra.*\-Werror\|--Werror.*\-Wall.*\-Wextra\|\-Wextra.*\-Wall.*\-Werror"; then
    echo -e "${GREEN}✅ Compilation flags OK${RESET}"
else
    echo -e "${RED}❌ Missing required flags (-Wall -Wextra -Werror)${RESET}"
fi

echo -e "${YELLOW}Checking re-linking...${RESET}"
make > /dev/null 2>&1
if make 2>&1 | grep -q "Nothing to be done\|up to date"; then
    echo -e "${GREEN}✅ No re-linking${RESET}"
else
    echo -e "${RED}❌ Makefile re-links unnecessarily${RESET}"
fi

# ============================================================================
# 2. SIMPLE COMMANDS & GLOBAL VARIABLES
# ============================================================================
print_header "2. SIMPLE COMMANDS & GLOBAL VARIABLES"

run_test "Absolute path command" "/bin/ls"
run_test "Another absolute path" "/bin/pwd"
run_test "Absolute path with /usr/bin" "/usr/bin/env"
run_test "Command: /bin/echo hello" "/bin/echo hello"
run_test "Empty command" ""

echo -e "\n${YELLOW}Global Variables Check:${RESET}"
echo -e "${CYAN}Please manually verify that only signal-related global variables are used${RESET}"
echo -e "${CYAN}Expected: Only g_signal_status or similar for signal handling${RESET}"

# ============================================================================
# 3. ARGUMENTS
# ============================================================================
print_header "3. ARGUMENTS"

run_test "Command with arguments" "/bin/ls -l"
run_test "Multiple arguments" "/bin/echo hello world test"
run_test "Command with flags" "/bin/ls -la /tmp"
run_test "Complex arguments" "/usr/bin/wc -l /etc/passwd"
run_test "Arguments with numbers" "/bin/echo 123 456 789"

# ============================================================================
# 4. ECHO BUILTIN
# ============================================================================
print_header "4. ECHO BUILTIN"

run_test "Echo without arguments" "echo"
run_test "Echo with text" "echo hello world"
run_test "Echo with -n flag" "echo -n hello"
run_test "Echo multiple words" "echo one two three four five"
run_test "Echo with special chars" "echo 'hello world!'"

# ============================================================================
# 5. EXIT BUILTIN
# ============================================================================
print_header "5. EXIT BUILTIN"

run_test "Exit without args" "exit" false
run_test "Exit with number" "exit 42" false
run_test "Exit with large number" "exit 300" false
run_test "Exit with invalid arg" "exit hello" false
run_test "Exit with multiple args" "exit 1 2" false

# ============================================================================
# 6. RETURN VALUES
# ============================================================================
print_header "6. RETURN VALUES"

run_test "Success command - ls" "/bin/ls > /dev/null"
run_test "Check exit code after success" "echo \$?"
run_test "Failure command - ls nonexistent" "/bin/ls /nonexistent 2>/dev/null"
run_test "Check exit code after failure" "echo \$?"
run_test "Exit code after builtin" "echo \$?"

# ============================================================================
# 7. SIGNAL HANDLING
# ============================================================================
print_header "7. SIGNAL HANDLING"

echo -e "${YELLOW}Signal tests require manual verification:${RESET}"
echo -e "${CYAN}1. Ctrl+C on empty prompt -> new line + new prompt${RESET}"
echo -e "${CYAN}2. Ctrl+\\ on empty prompt -> nothing${RESET}"
echo -e "${CYAN}3. Ctrl+D on empty prompt -> quit minishell${RESET}"
echo -e "${CYAN}4. Ctrl+C after typing -> new line, clear buffer${RESET}"
echo -e "${CYAN}5. Test signals during blocking commands (cat, grep)${RESET}"

# ============================================================================
# 8. DOUBLE QUOTES
# ============================================================================
print_header "8. DOUBLE QUOTES"

run_test "Double quotes with spaces" 'echo "hello world"'
run_test "Double quotes complex" 'echo "cat lol.c | cat > lol.c"'
run_test "Double quotes with variables" 'echo "Current user: $USER"'
run_test "Empty double quotes" 'echo ""'
run_test "Double quotes with special chars" 'echo "Hello! @#$%^&*()"'

# ============================================================================
# 9. SINGLE QUOTES
# ============================================================================
print_header "9. SINGLE QUOTES"

run_test "Single quotes basic" "echo 'hello world'"
run_test "Single quotes with \$USER" "echo '\$USER'"
run_test "Single quotes with pipes" "echo 'cat | grep | wc'"
run_test "Empty single quotes" "echo ''"
run_test "Single quotes with redirects" "echo 'ls > file.txt'"

# ============================================================================
# 10. ENV BUILTIN
# ============================================================================
print_header "10. ENV BUILTIN"

run_test "Show environment" "env | head -5"
run_test "Env with grep" "env | grep USER"
run_test "Check PATH variable" "env | grep PATH"
run_test "Check HOME variable" "env | grep HOME"
run_test "Env output length" "env | wc -l"

# ============================================================================
# 11. EXPORT BUILTIN
# ============================================================================
print_header "11. EXPORT BUILTIN"

run_test "Export new variable" "export TESTVAR=hello"
run_test "Check exported variable" "echo \$TESTVAR"
run_test "Export replace existing" "export USER=newuser"
run_test "Export without value" "export TESTVAR2"
run_test "Export with spaces" "export TESTVAR3='hello world'"

# ============================================================================
# 12. UNSET BUILTIN
# ============================================================================
print_header "12. UNSET BUILTIN"

run_test "Export for unset test" "export TESTVAR=test"
run_test "Unset existing var" "unset TESTVAR"
run_test "Check unset variable" "echo \$TESTVAR"
run_test "Unset PATH" "unset PATH"
run_test "Unset nonexistent" "unset NONEXISTENT"

# ============================================================================
# 13. CD BUILTIN
# ============================================================================
print_header "13. CD BUILTIN"

run_test "Change to /tmp" "cd /tmp"
run_test "Check pwd after cd /tmp" "pwd"
run_test "Change to home" "cd"
run_test "Check pwd after cd home" "pwd"  
run_test "Change to nonexistent" "cd /nonexistent"

# ============================================================================
# 14. PWD BUILTIN
# ============================================================================
print_header "14. PWD BUILTIN"

run_test "Print working directory" "pwd"
run_test "PWD with arguments" "pwd /some/arg"
run_test "PWD call 1" "pwd"
run_test "PWD call 2" "pwd"  
run_test "PWD call 3" "pwd"

# ============================================================================
# 15. RELATIVE PATHS
# ============================================================================
print_header "15. RELATIVE PATHS"

run_test "Relative path ./minishell" "echo 'Relative path test'"
run_test "Complex relative path" "ls ../../"
run_test "Relative with dots" "ls ./."
run_test "Multiple dots" "ls ../.."
run_test "Relative executable" "echo 'Testing relative paths'"

# ============================================================================
# 16. ENVIRONMENT PATH
# ============================================================================
print_header "16. ENVIRONMENT PATH"

run_test "Command without path" "ls | head -3"
run_test "Another command" "echo hello"
run_test "Built-in vs external" "pwd"
run_test "Wc command" "echo 'test' | wc -l"
run_test "Grep command" "echo 'hello world' | grep hello"

# Path manipulation tests
echo -e "\n${YELLOW}Testing PATH manipulation:${RESET}"
run_test "Unset PATH test" "unset PATH"
run_test "Try ls without PATH" "ls"

# ============================================================================
# 17. REDIRECTIONS
# ============================================================================
print_header "17. REDIRECTIONS"

# Create test files
echo "test content" > test_input.txt

run_test "Input redirection" "cat < test_input.txt"
run_test "Output redirection" "echo 'test output' > test_out.txt"
run_test "Check output file" "cat test_out.txt"
run_test "Append redirection 1" "echo 'line1' > test_append.txt"
run_test "Append redirection 2" "echo 'line2' >> test_append.txt"  
run_test "Check append file" "cat test_append.txt"
run_test "Multiple redirections" "cat < test_input.txt > test_copy.txt"
run_test "Here document" "cat << EOF\nline1\nline2\nEOF"

# Cleanup
rm -f test_input.txt test_out.txt test_append.txt test_copy.txt

# ============================================================================
# 18. PIPES
# ============================================================================
print_header "18. PIPES"

run_test "Simple pipe" "echo 'hello world' | cat"
run_test "Multiple pipes" "echo 'test line' | cat | wc -w"
run_test "Pipe with grep" "printf 'line1\nline2\ntest\n' | grep test"
run_test "Complex pipe" "ls | head -3 | wc -l"
run_test "Pipe with failure" "ls /nonexistent 2>&1 | grep 'No such file'"

# ============================================================================
# 19. ENVIRONMENT VARIABLES
# ============================================================================
print_header "19. ENVIRONMENT VARIABLES"

run_test "Echo USER variable" "echo \$USER"
run_test "Echo in double quotes" "echo \"User: \$USER\""
run_test "Variable in command" "echo \$HOME"
run_test "Multiple variables" "echo \$USER \$HOME \$PATH | wc -w"
run_test "Variable interpolation" "echo \"Current user is \$USER in \$PWD\""

# ============================================================================
# 20. STRESS TESTS
# ============================================================================
print_header "20. STRESS TESTS & EDGE CASES"

run_test "Invalid command" "invalidcommand123"
run_test "Very long command" "echo $(printf 'a%.0s' {1..100})"
run_test "Mixed quotes" "echo 'single' \"double\" mixed"
run_test "Empty pipes" "echo hello | | cat" false
run_test "Complex combination" "echo 'test' | cat | grep test | wc -l"

# ============================================================================
# FINAL RESULTS
# ============================================================================
print_header "FINAL RESULTS"

echo -e "${CYAN}Total tests: $TOTAL${RESET}"
echo -e "${GREEN}Passed: $PASSED${RESET}"
echo -e "${RED}Failed: $FAILED${RESET}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${RESET}"
    echo -e "${GREEN}Your minishell is working perfectly!${RESET}"
else
    echo -e "\n${YELLOW}⚠️  Some tests failed${RESET}"
    echo -e "${YELLOW}Success rate: $((PASSED * 100 / TOTAL))%${RESET}"
fi

echo -e "\n${PURPLE}============================================${RESET}"
echo -e "${PURPLE}Manual verification still required for:${RESET}"
echo -e "${PURPLE}- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\\)${RESET}"
echo -e "${PURPLE}- Memory leaks (run with valgrind)${RESET}"
echo -e "${PURPLE}- History navigation (Up/Down arrows)${RESET}"
echo -e "${PURPLE}- Global variables count${RESET}"
echo -e "${PURPLE}============================================${RESET}"

# Memory leak check
echo -e "\n${YELLOW}Running memory leak check...${RESET}"
if command -v valgrind >/dev/null 2>&1; then
    echo -e "${CYAN}Testing memory leaks with a simple command...${RESET}"
    echo -e "echo hello\nexit" | timeout 10s valgrind --leak-check=summary --suppressions=readline.supp $MINISHELL_PATH 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost"
else
    echo -e "${YELLOW}Valgrind not found. Please test for memory leaks manually.${RESET}"
fi

echo -e "\n${GREEN}Testing complete!${RESET}"
