#!/bin/bash

mkdir -p ../build || exit
cd ../build

cmake ..

make && sudo make install
