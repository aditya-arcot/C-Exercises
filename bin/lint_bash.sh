#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: lint_bash.sh <file1.sh> [file2.sh ...]"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        echo "Linting $file"
        if ! shellcheck "$file"; then
            printf "\nIssues found in %s\n" "$file"
            exit 1
        fi
    else
        echo "File '$file' not found"
        exit 1
    fi
done

echo "Done linting Bash files"
