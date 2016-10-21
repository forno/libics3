# The libics3
The c++ API of ICS3.x communication for drive servo motors on Linux.

## Description
libics3 is c++ API for drive servo motors
that suport ICS3.5 or after serial communication.

ex)[KRS series servo moters produced by KONDO KAGAKU co., ltd.](http://kondo-robot.com/product-category/servomotor/krs)

## CAPTION
1. This software only support serial mode. You should lock the serial mode for never turn on PWM mode.
2. Linux need setup a serial USB adaptor for use it. `script/setup.sh` will mount it to `/dev/ttyUSB0`.

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
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/libics3
make
make install
```
You need to specify `cmake -Dlibics3_DIR=$HOME/libics3/lib/cmake/libics3`
for CMake based third-party application to find libics3.

Or, you can remove `CMAKE_INSTALL_PREFIX` parameter on this installation,
and you maybe need `sudo` for `make install` this way,
and system can find to libics3 without your specify.

ex)

```bash
cmake ..
make
sudo make install
```

## LICENSE
This software is released under the BSD 2-Clause License, see LICENSE.txt.
