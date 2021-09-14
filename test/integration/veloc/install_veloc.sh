#!/bin/bash

git clone -b 'veloc-1.4' --depth 1 https://github.com/ECP-VeloC/veloc.git lib
cd lib
./bootstrap.sh
mkdir build
./auto-install.py --temp temp build