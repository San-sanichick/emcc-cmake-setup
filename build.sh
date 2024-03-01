#!/bin/bash

# activate emscripten variables
export EMSDK_QUIET=1
source ./vendors/emsdk/emsdk_env.sh

# setup and run cmake and make
emcmake cmake . -DCMAKE_BUILD_TYPE=Release
emmake make index
