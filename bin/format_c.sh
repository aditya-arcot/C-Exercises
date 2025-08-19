#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: format_c.sh <file1.c> [file2.c ...]"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        if [[ "$file" =~ \.c$ || "$file" =~ \.h$ ]]; then
            echo "Formatting $file"
            clang-format -i "$file"
        else
            echo "File '$file' is not a C file"
        fi
    else
        echo "File '$file' not found"
        exit 1
    fi
done

echo "Done formatting C files"
