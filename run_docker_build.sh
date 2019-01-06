#!/bin/sh

set -xe

git clone https://github.com/openturns/openturns.git /tmp/openturns
cd /tmp/openturns
cmake -DCMAKE_INSTALL_PREFIX=~/.local -DBUILD_PYTHON=OFF -DUSE_COTIRE=ON -DCOTIRE_MAXIMUM_NUMBER_OF_UNITY_INCLUDES="-j16" .
make install

cd /tmp
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=~/.local -DOpenTURNS_DIR=~/.local/lib/cmake/openturns /io
make install
ctest --output-on-failure --timeout 100 ${MAKEFLAGS}
