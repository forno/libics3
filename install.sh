#!/bin/bash

mkdir -p build || exit

cd build
cmake ..

sudo make install
