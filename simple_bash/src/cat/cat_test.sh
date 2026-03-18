#!/bin/bash

passed=0
failed=0

# Testing file
source_file="./s21_cat"

if [ ! -f "$source_file" ]; then
    echo "File $source_file not found"
    exit 1
fi

run(){
    local args="$1"
    local desc="$2"

    local system_cat_args="$args"

    cat $system_cat_args > system_cat.txt 2>&1
    ./s21_cat $args > s21_cat.txt 2>&1

    sed -E 's/^[a-zA-Z0-9_.-]+: //' system_cat.txt > system_clean.txt

    if diff -q system_clean.txt s21_cat.txt > /dev/null 2>&1; then
        echo "[PASS]: $desc"
        ((passed++))
    else
        echo "[FAILED]: $desc"
        echo "Difference: "
        diff system_clean.txt s21_cat.txt
        echo "------------------------------------"
        ((failed++))
    fi
    
    rm -f system_clean.txt system_cat.txt s21_cat.txt
}

mkdir -p tests

# Empty file
> tests/test_empty.txt

# Single line
echo "Hello world" > tests/test_single.txt

# Mixed lines
echo -e "First line\n\n\nSecond line\nThird line\n\nFifth line" > tests/test_mixed.txt

# Tabs and specials
echo -e "Normal line\n\tTab at start\nMiddle\tTab\n\tMultiple\t\ttabs\nLine with \\r\\n special\nLine with form feed\f\nLine with vertical tab\v" > tests/test_tabs.txt

# Non-printable
echo -e "Hello\x01World\x02\n\x07Bell\x08Backspace\n\x0BVertical\x0CForm\n\x1C\x1D\x1E\x1F\nLine with DEL\x7F" > tests/test_nonprint.txt

# Boundary values
echo -e "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\n\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1C\x1D\x1E\x1F\x20\n\x7F\n\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\n\xFF" > tests/test_boundary.txt

# File with many empty lines
echo -e "1\n\n2\n\n\n3\n\n\n\n4" > tests/test_consecutive.txt

echo "==================================="
echo "STARTING TEST..."
echo "==================================="

# On empty file
run "-n tests/test_empty.txt" "Flag -n on empty file"
run "-b tests/test_empty.txt" "Flag -b on empty file" 
run "-s tests/test_empty.txt" "Flag -s on empty file"
run "-e tests/test_empty.txt" "Flag -e on empty file"
run "-t tests/test_empty.txt" "Flag -t on empty file"

# On single line
run "-n tests/test_single.txt" "Flag -n on single line"
run "-b tests/test_single.txt" "Flag -b on single line"
run "-e tests/test_single.txt" "Flag -e on single line"
run "-t tests/test_single.txt" "Flag -t on single line"

# On mixed lines
run "tests/test_mixed.txt" "No flags (mixed empty lines)"
run "-n tests/test_mixed.txt" "Flag -n on mixed empty lines"
run "-b tests/test_mixed.txt" "Flag -b on mixed empty lines"
run "-s tests/test_mixed.txt" "Flag -s on mixed empty lines"
run "-e tests/test_mixed.txt" "Flag -e on mixed empty lines"
run "-t tests/test_mixed.txt" "Flag -t on mixed empty lines"

# On tabs
run "tests/test_tabs.txt" "No flags (tabs and specials)"
run "-t tests/test_tabs.txt" "Flag -t on tabs"
run "-T tests/test_tabs.txt" "Flag -T on tabs (show tabs only)"
run "-e tests/test_tabs.txt" "Flag -e on tabs (show ends)"

# On non-printable
run "tests/test_nonprint.txt" "No flags (non-printable)"
run "-e tests/test_nonprint.txt" "Flag -e on non-printable"
run "-t tests/test_nonprint.txt" "Flag -t on non-printable"

# On boundary values
run "-e tests/test_boundary.txt" "Flag -e on boundary values"
run "-t tests/test_boundary.txt" "Flag -t on boundary values"

#On consecutive empty lines
run "tests/test_consecutive.txt" "No flags (consecutive empty lines)"
run "-s tests/test_consecutive.txt" "Flag -s on consecutive empty lines"
run "-n tests/test_consecutive.txt" "Flag -n on consecutive empty lines"
run "-b tests/test_consecutive.txt" "Flag -b on consecutive empty lines"

# Error cases
run "nonexistent_file.txt" "Non-existent file"
run "-n nonexistent_file.txt" "Non-existent file with -n"

# GNU long options
run "--number tests/test_mixed.txt" "GNU --number"
run "--number-nonblank tests/test_mixed.txt" "GNU --number-nonblank"
run "--squeeze-blank tests/test_consecutive.txt" "GNU --squeeze-blank"

echo "==================================="
echo "RESULTS"
echo "==================================="
echo "[PASSED]: $passed"
echo "[FAILED]: $failed"

rm -rf tests