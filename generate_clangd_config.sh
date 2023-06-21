#!/usr/bin/env bash

INCLUDE_PATH="${HOME}/Desktop/devCode/cppDev/CPP_APIs/dependencies/include"
CLANGD_CONFIG=".clangd"

# Check if .clangd file exists
if [ -e "$CLANGD_CONFIG" ]; then
    # If .clangd file already exists, update the include path
    sed -i "s|-I.*|-I${INCLUDE_PATH}|" "$CLANGD_CONFIG"
else
    # If .clangd file doesn't exist, create it with the include path
    echo "CompileFlags:" > "$CLANGD_CONFIG"
    echo "  Add:" >> "$CLANGD_CONFIG"
    echo "    - -I${INCLUDE_PATH}" >> "$CLANGD_CONFIG"
fi

