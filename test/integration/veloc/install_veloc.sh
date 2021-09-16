#!/bin/bash

git clone -b '1.5' --depth 1 https://github.com/ECP-VeloC/veloc.git lib && cd lib && mkdir install && ./bootstrap.sh && ./auto-install.py install