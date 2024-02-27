#!/usr/bin/env bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    ln -sf .clangd-linux .clangd
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ln -sf .clangd-macos .clangd
fi
