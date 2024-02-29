#!/bin/bash

# emcmake cmake .
# cd build
export EMSDK_QUIET=1
source ./vendors/emsdk/emsdk_env.sh

emcmake cmake .
emmake make
make index