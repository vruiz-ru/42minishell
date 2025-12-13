# 🔥 COMPREHENSIVE MINISHELL EVALUATION CHECKLIST 🔥

Based on the 42 evaluation criteria, this document provides a detailed checklist for testing minishell functionality against bash behavior.

## 📋 EVALUATION CHECKLIST

### ✅ **1. COMPILATION (Mandatory)**
- [ ] `make -n` shows `-Wall -Wextra -Werror` flags
- [ ] Project compiles without errors
- [ ] Makefile doesn't re-link when no changes made
- [ ] No forbidden functions used (check subject)

### ✅ **2. SIMPLE COMMANDS & GLOBAL VARIABLES**
**Commands to test:**
```bash
/bin/ls
/bin/pwd  
/usr/bin/env
/bin/echo hello
[empty command - just press Enter]
```
**Global Variables Check:**
- [ ] How many global variables? (Should be minimal)
- [ ] Global variables only for signal handling
- [ ] Student can explain why each global variable is needed

### ✅ **3. ARGUMENTS**
**Commands to test:**
```bash
/bin/ls -l
/bin/echo hello world test
/bin/ls -la /tmp
/usr/bin/wc -l /etc/passwd
/bin/echo 123 456 789
```

### ✅ **4. ECHO BUILTIN**
**Commands to test:**
```bash
echo
echo hello world
echo -n hello
echo one two three four five
echo "hello world with spaces"
```

### ✅ **5. EXIT BUILTIN**
**Commands to test:** (Remember to relaunch minishell after each!)
```bash
exit
exit 42
exit 300
exit hello
exit 1 2 3
```

### ✅ **6. RETURN VALUES ($?)**
**Commands to test:**
```bash
/bin/ls > /dev/null; echo $?
/bin/ls /nonexistent 2>/dev/null; echo $?
echo $?; expr $? + $?
/bin/true; echo $?; /bin/false; echo $?
echo hello; echo $?
```

### ✅ **7. SIGNAL HANDLING (Manual Testing Required)**
**Test Matrix:**

| Situation | Ctrl+C | Ctrl+\\ | Ctrl+D |
|-----------|--------|---------|--------|
| Empty prompt | New line + prompt | Nothing | Quit minishell |
| After typing text | New line + clean buffer | Nothing | Nothing |
| During blocking command (cat/grep) | Interrupt | Nothing | EOF to command |

**Blocking commands to test:**
```bash
cat
grep "something"
sleep 10
```

### ✅ **8. DOUBLE QUOTES**
**Commands to test:**
```bash
echo "hello world"
echo "cat lol.c | cat > lol.c"
echo "Current user: $USER"
echo ""
echo "Special chars: !@#$%^&*()"
```

### ✅ **9. SINGLE QUOTES**
**Commands to test:**
```bash
echo 'hello world'
echo '$USER'  # Should print literal $USER
echo 'cat | grep | wc'
echo ''
echo 'Special chars: !@#$%^&*()'
```

### ✅ **10. ENV BUILTIN**
**Commands to test:**
```bash
env
env | grep USER
env | grep PATH
env | wc -l
```

### ✅ **11. EXPORT BUILTIN**
**Commands to test:**
```bash
export TESTVAR=hello; echo $TESTVAR
export USER=newuser; env | grep USER
export TESTVAR2
export TESTVAR3="hello world"
export A=1 B=2; echo $A $B
```

### ✅ **12. UNSET BUILTIN**
**Commands to test:**
```bash
export TESTVAR=test; unset TESTVAR; echo $TESTVAR
unset PATH; ls  # Should fail
export A=1 B=2; unset A B; echo $A $B
unset NONEXISTENT
```

### ✅ **13. CD BUILTIN**
**Commands to test:**
```bash
cd /tmp; pwd
cd; pwd  # Should go to HOME
cd .; pwd
cd ..; pwd
cd /nonexistent  # Should show error
```

### ✅ **14. PWD BUILTIN**
**Commands to test:**
```bash
pwd
cd /tmp; pwd
cd ..; pwd
pwd /some/arg  # Test with arguments
```

### ✅ **15. RELATIVE PATHS**
**Commands to test:**
```bash
./minishell  # If available
ls ../../
ls ./.
ls ../..
echo "test" > temp.txt; cat ./temp.txt; rm temp.txt
```

### ✅ **16. ENVIRONMENT PATH**
**Commands to test:**
```bash
ls  # Without /bin/
echo hello
wc
grep
# Then test PATH manipulation:
unset PATH; ls  # Should fail
export PATH="/bin:/usr/bin"; ls  # Should work
```

### ✅ **17. REDIRECTIONS**
**Commands to test:**
```bash
echo "test" > outfile; cat outfile; rm outfile
echo "content" > file.txt; cat < file.txt; rm file.txt
echo "line1" > file.txt; echo "line2" >> file.txt; cat file.txt; rm file.txt
cat << EOF
line1
line2
EOF
ls > /dev/null 2>&1
```

### ✅ **18. PIPES**
**Commands to test:**
```bash
echo "hello world" | cat
ls | head -3
echo -e "line1\nline2\ntest" | grep test
cat /etc/passwd | head -5 | wc -l
ls /nonexistent 2>&1 | grep "No such file"
```

### ✅ **19. ENVIRONMENT VARIABLES**
**Commands to test:**
```bash
echo $USER
echo "$USER"
echo $HOME
echo "$USER is in $PWD"
echo $NONEXISTENT  # Should be empty
```

### ✅ **20. ADVANCED & STRESS TESTS**
**Commands to test:**
```bash
invalidcommand123
dsbksdgbksdghsd
cat | cat | ls
echo $(printf 'a%.0s' {1..1000})  # Very long argument
echo 'single' "double" mixed
history  # Test if available
# Navigate with Up/Down arrows
```

## 🔍 **MEMORY LEAK TESTING**
```bash
# Using valgrind
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Using leaks (macOS)
leaks --atExit -- ./minishell

# Test with commands that allocate memory
echo "Memory test commands:"
echo $USER
export TEST=value; unset TEST
ls | grep something
cat << EOF > /dev/null
test
EOF
```

## 🚨 **RED FLAGS (Instant Failure)**
- [ ] **Segmentation fault** during any test
- [ ] **Memory leaks** detected
- [ ] **Compilation errors**
- [ ] **Norm errors**
- [ ] **Cheating/plagiarism**
- [ ] **Unexpected program termination**

## ⭐ **BONUS POINTS TO CHECK**
- [ ] **History navigation** (Up/Down arrows)
- [ ] **Advanced redirections** (multiple, complex)
- [ ] **Advanced pipes** (complex chains)
- [ ] **Error handling** (graceful error messages)
- [ ] **Performance** (handles large inputs)

## 📊 **SCORING GUIDELINES**

| Score | Criteria |
|-------|----------|
| 125/100 | Perfect implementation + bonus features |
| 100/100 | All mandatory requirements met perfectly |
| 80-99/100 | Minor issues, most features work |
| 60-79/100 | Some major features missing/broken |
| 40-59/100 | Basic functionality only |
| 0-39/100 | Significant problems, many failures |
| 0/100 | Doesn't compile, crashes, or norm errors |
| -42/100 | Cheating detected |

## 🎯 **COMPARISON WITH BASH**

For each test, compare the behavior with bash:
```bash
# Test in bash first
bash
[command]
exit

# Then test in minishell
./minishell
[same command]
exit
```

**What to compare:**
- Output format and content
- Exit codes (`echo $?`)
- Error messages
- Behavior with edge cases
- Signal handling response

## 📝 **EVALUATION NOTES TEMPLATE**

```
Student(s): _______________
Date: ___________________

COMPILATION:
□ Makefile flags correct
□ Compiles without errors  
□ No re-linking
Issues: ________________

MANDATORY FEATURES:
□ Simple commands: ___/5
□ Arguments: ___/5
□ Built-ins (echo, cd, pwd, export, unset, env, exit): ___/7
□ Redirections: ___/5
□ Pipes: ___/5  
□ Environment variables: ___/5
□ Signal handling: ___/5
□ Return values: ___/5

GLOBAL VARIABLES:
Count: ___
Purpose: _______________
Acceptable: □ Yes □ No

MEMORY LEAKS:
□ No leaks detected
□ Minor leaks
□ Major leaks
Tool used: ___________

BONUS FEATURES:
□ History
□ Advanced features
□ Error handling

OVERALL IMPRESSION:
□ Excellent (125)
□ Very good (100-110)  
□ Good (85-99)
□ Acceptable (70-84)
□ Poor (50-69)
□ Failure (0-49)

FINAL SCORE: ___/100
```

---

**Remember:** This evaluation should be thorough but fair. The goal is to help the student learn and improve their implementation while ensuring they meet the project requirements.
