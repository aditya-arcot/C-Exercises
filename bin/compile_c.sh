#!/bin/bash

set -euo pipefail

OUTFILE="program.out"
EXECUTE=true
PRESERVE=true
SEPARATE=false
ARGS=()
OUTPUTS=()
CFLAGS=(-std=c17 -g -O0 -Werror -Wall -Wextra -Wpedantic)
COMP_START=false
COMP_COUNT=0
COMP_ERR_COUNT=0

show_help() {
    cat << EOF
Usage: $(basename "$0") [options] file1.c [file2.c ...]

Options:
  -o file       Output file name
  -e            Don't execute compiled program
  -p            Don't preserve output files
  -s            Compile each source file separately
  -a arg        Command-line argument for compiled program
  -h            Display this help message

Defaults:
  Execute       true
  Preserve      true
  Separate      false

Examples:
  $(basename "$0") -eps file1.c file2.c
  $(basename "$0") -o custom.out -a "arg1 arg2" file1.c file2.c
EOF
}

error() {
    echo "Error: $*" >&2
    exit 1
}

compilation_error() {
    echo "Compilation Error: $*" >&2
    COMP_ERR_COUNT=$((COMP_ERR_COUNT + 1))
}

separator() {
    printf '%*s\n' "$(tput cols)" '' | tr ' ' '='
}

cleanup() {
    if $COMP_START; then
        if ! $PRESERVE; then
            separator
            echo "Cleaning up..."
            for f in "${OUTPUTS[@]-}"; do
                if [[ -f "$f" ]]; then
                    echo "Removing $f"
                    rm -f "$f"
                fi
                if [[ -d "$f.dSYM" ]]; then
                    echo "Removing $f.dSYM"
                    rm -rf "$f.dSYM"
                fi
            done
        fi
        separator
        echo "Finished after $COMP_COUNT compilation(s) with $COMP_ERR_COUNT error(s)"
        if [[ $COMP_ERR_COUNT -gt 0 ]]; then
            exit 1
        fi
    fi
}
trap cleanup EXIT

interrupt() {
    echo
    separator
    echo "Interrupt signal received"
    cleanup
    trap - EXIT
    exit 1
}

while getopts ":o:epsa:h" opt; do
    case $opt in
        o)
            if [[ -z "$OPTARG" || "$OPTARG" == -* ]]; then
                error "Option -o requires an argument"
            fi
            OUTFILE="$OPTARG"
            ;;
        e) EXECUTE=false ;;
        p) PRESERVE=false ;;
        s) SEPARATE=true ;;
        a)
            if [[ -z "$OPTARG" ]]; then
                error "Option -a requires at least one argument"
            fi
            # split quoted args into array
            read -ra ARGWORDS <<< "$OPTARG"
            ARGS+=("${ARGWORDS[@]}")
            ;;
        h)
            show_help
            exit 0
            ;;
        \?) error "Invalid option: -$OPTARG" ;;
        :) error "Option -$OPTARG requires an argument" ;;
    esac
done
shift $((OPTIND - 1))

C_FILES=()
for arg in "$@"; do
    [[ "$arg" =~ \.c$ ]] || error "Invalid file: $arg (must end in .c)"
    [[ -f "$arg" ]] || error "File not found: $arg"
    C_FILES+=("$arg")
done
[[ ${#C_FILES[@]} -gt 0 ]] || error "No .c files provided"

if $SEPARATE && [[ "$OUTFILE" != "program.out" ]]; then
    echo "Warning: --output is ignored when using --separate mode"
    separator
fi

COMP_START=true

compile_and_execute() {
    local out="$1"
    shift
    local srcs=("$@")
    COMP_COUNT=$((COMP_COUNT + 1))

    echo "Compiling: ${srcs[*]} -> $out"
    if cc "${CFLAGS[@]}" -o "$out" "${srcs[@]}"; then
        echo "Compilation successful: $out"
        OUTPUTS+=("$out")

        if $EXECUTE; then
            echo "Executing $out:"
            separator
            trap interrupt SIGINT

            set +e
            if [[ ${#ARGS[@]} -gt 0 ]]; then
                "./$out" "${ARGS[@]}"
            else
                "./$out"
            fi
            exit_code=$?
            set -e
            separator

            echo "Execution finished"
            if [[ $exit_code -ne 0 ]]; then
                compilation_error "Exit code $exit_code"
            fi
        else
            echo "Execution skipped"
            if $PRESERVE; then
                echo "Output preserved at $out"
            fi
        fi
    else
        compilation_error "Compilation failed: ${srcs[*]}"
    fi
}

if $SEPARATE; then
    FIRST=true
    for FILE in "${C_FILES[@]}"; do
        BASE=$(basename "$FILE" .c)
        OUTFILE="$BASE.out"

        if ! $FIRST; then
            separator
        fi
        FIRST=false

        compile_and_execute "$OUTFILE" "$FILE"
    done
else
    compile_and_execute "$OUTFILE" "${C_FILES[@]}"
fi
