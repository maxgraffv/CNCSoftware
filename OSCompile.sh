#!/bin/bash

PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"

SOURCES=$(find "$PROJECT_ROOT/src" -name "*.cpp")

INCLUDES="\
    -I$PROJECT_ROOT/include/core \
    -I$PROJECT_ROOT/include/motion \
    -I$PROJECT_ROOT/include/gcode \
    -I$PROJECT_ROOT/include/tools \
    -I$PROJECT_ROOT/include/hal \
    -I$PROJECT_ROOT/include/config"

g++ $SOURCES $INCLUDES -o "$PROJECT_ROOT/cncOS" \
    -lwiringPi -std=c++20 -Wall -Wextra -O2

