#!/bin/bash

set -euo pipefail

STASHED=false

cleanup_on_fail() {
    if $STASHED; then
        echo "Restoring stashed changes (pre-commit)"
        git stash pop -q
    fi
}
trap cleanup_on_fail ERR INT TERM

echo "Checking for unstaged changes"
if ! git diff --quiet; then
    echo "Stashing unstaged changes"
    git stash -k
    STASHED=true
fi

STAGED_BASH_FILES=$(git diff --cached --name-only --diff-filter=AM | grep -E '\.sh$' || true)
if [ -n "$STAGED_BASH_FILES" ]; then
    echo "Formatting Bash files"
    echo "$STAGED_BASH_FILES" | xargs format_bash.sh
    echo "$STAGED_BASH_FILES" | xargs git add
    echo

    echo "Linting Bash files"
    echo "$STAGED_BASH_FILES" | xargs lint_bash.sh
    echo
fi

STAGED_C_FILES=$(git diff --cached --name-only --diff-filter=AM | grep -E '\.(c|h)$' || true)
if [ -n "$STAGED_C_FILES" ]; then
    echo "Formatting C files"
    echo "$STAGED_C_FILES" | xargs format_c.sh
    echo "$STAGED_C_FILES" | xargs git add
    echo
fi

STAGED_FILES=$(git diff --cached --name-only --diff-filter=AM || true)
if [ -n "$STAGED_FILES" ]; then
    echo "Formatting files with Prettier"
    echo "$STAGED_FILES" | xargs npx -y prettier -w --ignore-unknown
    echo "$STAGED_FILES" | xargs git add
    echo
fi

if $STASHED; then
    echo "Creating stashed flag file"
    touch .git/pre_commit_stashed
    echo
fi
