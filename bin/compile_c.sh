#!/bin/bash

show_help() {
    echo "Usage: compile_c.sh [options] file1.c [file2.c ... fileN.c]"
    echo ""
    echo "Options:"
    echo "  -n, --no-execute    Don't execute the compiled program"
    echo "  -o, --output        Specify the output file name"
    echo "  -h, --help          Display this help message"
}

separator() {
    printf '%*s\n' "$(tput cols)" '' | tr ' ' '='
}

cleanup() {
    echo
    separator
    printf "Interrupt signal. Removing %s\n" "$OUTFILE"
    rm -f "$OUTFILE"
    exit 1
}

EXECUTE=true
OUTFILE="program.out"

while [[ "$1" == -* ]]; do
    case $1 in
        -n | --no-execute)
            EXECUTE=false
            ;;
        -o | --output)
            shift
            OUTFILE="$1"
            ;;
        -h | --help)
            show_help
            exit
            ;;
        *)
            echo "Invalid option: $1"
            show_help
            exit 1
            ;;
    esac
    shift
done

if [ "$#" -lt 1 ]; then
    echo "No files provided"
    show_help
    exit 1
fi

C_FILES=()
for arg in "$@"; do
    if [[ "$arg" =~ \.c$ ]]; then
        C_FILES+=("$arg")
    else
        echo "Invalid file name: $arg"
        show_help
        exit 1
    fi
done

if [ "${#C_FILES[@]}" -eq 0 ]; then
    echo "No valid .c files provided"
    show_help
    exit 1
fi

echo "Compiling files: ${C_FILES[*]} to $OUTFILE"
if cc -Weverything -Wno-poison-system-directories -Wno-declaration-after-statement -std=c17 -o "$OUTFILE" "${C_FILES[@]}"; then
    echo "Compilation successful"
    if $EXECUTE; then
        echo "Executing $OUTFILE:"
        separator
        trap cleanup SIGINT
        "./$OUTFILE"
        separator
        echo "Execution finished. Removing $OUTFILE"
        rm "$OUTFILE"
    else
        echo "Execution skipped. Preserving $OUTFILE"
    fi
else
    echo "Compilation failed"
    exit 1
fi
