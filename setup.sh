#!/bin/bash

echo "Adding bin folder to PATH"
export PATH="$PATH:$PWD/bin"

echo "Setting git hooks path"
git config core.hooksPath hooks/
