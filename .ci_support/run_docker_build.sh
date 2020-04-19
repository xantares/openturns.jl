#!/bin/sh

set -xe

cd /tmp
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=~/.local /io
make install
ctest --output-on-failure --timeout 100 ${MAKEFLAGS}

