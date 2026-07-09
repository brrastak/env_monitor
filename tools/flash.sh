#!/usr/bin/env bash

set -euo pipefail

./tools/build.sh

openocd \
    -f interface/stlink.cfg \
    -f target/stm32f4x.cfg \
    -c "program build/env_monitor.elf verify exit reset"
