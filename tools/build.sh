 #!/usr/bin/env bash

set -euo pipefail

BUILD_TYPE="${BUILD_TYPE:-Debug}"
BUILD_DIR="${BUILD_DIR:-build}"

echo "Configuring project..."
cmake -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake

echo "Building project..."
cmake --build "$BUILD_DIR" -- -j"$(nproc)"

echo "Build completed successfully."
