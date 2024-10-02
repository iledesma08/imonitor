#!/bin/bash

# Compile the source code
gcc -std=c11 -Iinclude -o executable src/expose_metrics.c src/main.c src/metrics.c -lpthread -lprom -lpromhttp -lmicrohttpd

# Set the LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Run the executable
./executable
