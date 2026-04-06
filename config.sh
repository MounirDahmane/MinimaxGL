#!/bin/bash

# If a build directory exists but contains a different generator's cache, clear it
if [ -d "build" ]; then
    if [ -f "build/CMakeCache.txt" ]; then
        if ! grep -q "CMAKE_GENERATOR:INTERNAL=Ninja" "build/CMakeCache.txt"; then
            echo "Detected generator mismatch. Cleaning build directory..."
            rm -rf build/*
        fi
    fi
fi

mkdir -p build

# Configure with Ninja and Release flags
cmake -S . -B build \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "------------------------------------------"
echo "Configuration Complete. Build with run.sh"
echo "------------------------------------------"