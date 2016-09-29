# The libics3
The c++ API of ICS3.x communication for drive servo motors on Linux.

## Description
libics3 is c++ API for drive servo motors
that suport ICS3.0 or after serial communication.

ex)[KRS series servo moters produced by KONDO KAGAKU co., ltd.](http://kondo-robot.com/product-category/servomotor/krs)

## CAPTION
This software only support serial mode.
if you use this on ICS3.5 or after,
You should lock the serial mode for never turn on PWM mode.

## API Reference
Reference [the libics3 wiki](https://github.com/forno/libics3/wiki)

## Installation
- Download libics3 source code

```sh
git clone https://github.com/forno/libics3.git
```
- Build

```sh
cd libics3
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/libics3
make
make install
```
You need to specify `cmake -Dlibics3_DIR=$HOME/libics3/lib/cmake/libics3`
for CMake based third-party application to find libics3.

Or, you can change CMAKE_INSTALL_PREFIX parameter on this installation.
ex) `cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local`

## LICENSE
This software is released under the BSD 2-Clause License, see LICENSE.txt.
