#!/bin/bash

set -euo pipefail

if [ -f .git/pre_commit_stashed ]; then
    echo "Found stashed flag file"
    echo "Restoring stashed changes (post-commit)"
    git stash pop -q || echo "warning - conflicts occurred while restoring stash"
    rm .git/pre_commit_stashed
    echo
fi
