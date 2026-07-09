#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build}"

echo "Removing build directory..."
rm -rf "$BUILD_DIR"

echo "Done."
