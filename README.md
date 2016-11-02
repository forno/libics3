# The libics3 [![Build Status](https://travis-ci.org/forno/libics3.svg?branch=master)](https://travis-ci.org/forno/libics3)
The c++ library of ICS3.x communication for drive servo motors on Linux.

## Description
libics3 is c++ library for drive servo motors
that suport ICS3.0 or newer serial communication.

ex)[KRS series servo moters produced by KONDO KAGAKU co., ltd.](http://kondo-robot.com/product-category/servomotor/krs)

## CAPTION
1. This software require c++11 compiler. In ubuntu 14.04 or after version have compiler support c++11.
2. This software only support serial mode. You should lock the serial mode for never turn on PWM mode.
3. Linux need serial device that mounted for use it. `script/setup.sh` will mount it to `/dev/ttyUSB0`.
4. The Makefile for debuging. You should take CMake for installation.

## API Reference
Reference [the libics3 wiki](https://github.com/forno/libics3/wiki)

## Installation
### Download libics3 source code

```sh
git clone https://github.com/forno/libics3.git
```
### Build

```sh
cd libics3
mkdir build && cd build
cmake ..
make
sudo make install
```

## LICENSE
This software is released under the BSD 2-Clause License, see LICENSE.txt.
