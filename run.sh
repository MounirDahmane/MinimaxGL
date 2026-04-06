#!/bin/bash

# Move to build directory
cd build || exit

# Compile using Ninja
# Ninja automatically detects the number of CPU cores
cmake --build .

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "------------------------------------------"
    echo "Build Successful. Launching TicTacToe..."
    echo "------------------------------------------"
    ./TicTacToe
else
    echo "------------------------------------------"
    echo "Build Failed. Check errors above."
    echo "------------------------------------------"
fi