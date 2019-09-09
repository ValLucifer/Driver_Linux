#!/bin/bash
chmod +x main.sh
export PATH=$PATH:./gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/
make main CROSS_COMPILE=aarch64-linux-gnu-
sync
