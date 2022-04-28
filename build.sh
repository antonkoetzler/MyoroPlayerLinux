#!/bin/sh
cmake -G "Unix Makefiles" -S ./ -B ./build
cd build
make
cp -r ../songs ./songs
$SHELL
