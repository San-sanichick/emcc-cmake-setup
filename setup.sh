#!/bin/bash

# activate emscripten
cd vendors/emsdk

./emsdk install latest
./emsdk activate latest

# # activate skia
cd ..
cd skia

python3 tools/git-sync-deps
bin/fetch-ninja
tools/install_dependencies.sh