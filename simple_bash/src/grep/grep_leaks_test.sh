#!/bin/bash

passed=0
failed=0

# Testing file
source_file="./s21_grep"

if [ ! -f "$source_file" ]; then
    echo "File $source_file not found"
    exit 1
fi

run(){
    local args="$1"
    local desc="$2"
    
    # Запускаем нашу программу
    valgrind --tool=memcheck --leak-check=yes ./s21_grep $args 2> valgrind.log

    if grep -q "ERROR SUMMARY: [1-9]" valgrind.log; then
        echo "[FAIL]: $desc"
        ((failed++))
    else
        ((passed++))
    fi
    
    rm -f valgrind.log
}

# Создаем тестовые файлы
mkdir -p test

cat > test/test.txt << 'EOF'
Hello world
hello Universe
Linux is great
hello again

123 test 456
hello
GOODBYE
EOF

touch test/empty.txt
cat > test/patterns.txt << 'EOF'
hello
world
EOF

echo "========================================="
echo "       STARTING GREP TESTS"
echo "========================================="
echo ""

run "hello test/test.txt" "Basic search 'hello'"
run "-i HELLO test/test.txt" "Case insensitive (-i)"
run "-v hello test/test.txt" "Invert match (-v)"
run "-c hello test/test.txt" "Count lines (-c)"
run "-l hello test/test.txt test/empty.txt" "Files with matches (-l)"
run "-n hello test/test.txt" "Line numbers (-n)"
run "-h hello test/test.txt test/test.txt" "No filename (-h)"
run "-s hello nonexistent.txt test/test.txt" "Suppress errors (-s)"
run "-f test/patterns.txt test/test.txt" "Pattern from file (-f)"
run "-e hello -e Linux test/test.txt" "Multiple patterns (-e)"
run "-o hello test/test.txt" "Only matching (-o)"
run "-in HELLO test/test.txt" "Combo: -i -n"
run "-iv HELLO test/test.txt" "Combo: -i -v"
run "-il HELLO test/test.txt" "Combo: -i -l"
run "-cv hello test/test.txt" "Combo: -c -v"
run "-c -l hello test/test.txt test/empty.txt" "Combo: -c -l"
run "hello test/empty.txt" "Empty file search"

echo ""
echo "==================================="
echo "RESULTS"
echo "==================================="
echo "[PASSED]: $passed"
echo "[FAILED]: $failed"

# Очистка
rm -rf test

if [ $failed -eq 0 ]; then
    exit 0
else
    exit 1
fi