#!/bin/bash
for X in *.gcov; do
    if [ "$X" != "FunctionalUtilities.h.gcov" ]; then
        rm "$X"
    fi
done