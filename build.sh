#!/usr/bin/env bash

cmake -S . -B dest -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=dest
cmake --build dest
#cmake --install dest
