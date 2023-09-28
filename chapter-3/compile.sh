#!/bin/bash

# Define the paths
V8_INCLUDE_DIR=./v8
V8_OUT_DIR=$V8_INCLUDE_DIR

# Check if a filename argument is provided
if [ -z "$1" ]; then
  echo "Usage: ./compile.sh <filename.cc>"
  exit 1
fi

# Get the filename from the command-line argument
FILENAME="$1"

# Extract the base filename without the extension
BASENAME=$(basename -- "$FILENAME")
BASENAME_NOEXT="${BASENAME%.*}"

# Compile the file
g++ -I$V8_INCLUDE_DIR -I$V8_INCLUDE_DIR/include \
    $FILENAME \
    -o $BASENAME_NOEXT -fno-rtti \
    -lv8_monolith -lv8_libbase -lv8_libplatform -ldl \
    -L$V8_OUT_DIR -pthread -std=c++17 -DV8_COMPRESS_POINTERS