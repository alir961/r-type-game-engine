#!/bin/bash

cmake -S . -B build/out -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake && clear && make -C build/out

if [ $? -eq 0 ]; then
	notify-send -u normal "R-Type Compilation" "Done."
else
	notify-send -u critical "R-Type Compilation" "Failed."
fi
