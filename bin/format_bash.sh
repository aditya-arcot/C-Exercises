#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: format_bash.sh <file1.sh> [file2.sh ...]"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        if [[ "$file" =~ \.sh$ ]]; then
            echo "Formatting $file"
            shfmt -w "$file"
        else
            echo "File '$file' is not a Bash file"
        fi
    else
        echo "File '$file' not found"
        exit 1
    fi
done

echo "Done formatting Bash files"
