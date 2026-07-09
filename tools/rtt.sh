#!/usr/bin/env bash
set -euo pipefail

PATH_TO_ELF="build/env_monitor.elf"
CHIP="STM32F401CCUx"


probe-rs attach \
    $PATH_TO_ELF \
    --chip "$CHIP"
