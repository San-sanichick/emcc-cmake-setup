#!/bin/bash

# clear target dir
echo "Clearing /target dir"
rm -rf target/*



# clear test dir
echo "Clearing /test dir"

cd test
GLOBIGNORE=index.html:test.js
rm -rf *
unset GLOBIGNORE
cd ..



# activate emscripten variables
export EMSDK_QUIET=1
source ./vendors/emsdk/emsdk_env.sh

# setup and run cmake and make
while [[ $# -gt 0 ]];
do
    case "$1" in
        -r|--release)
            emcmake cmake . -DCMAKE_BUILD_TYPE=Release
            echo "Building for release"
            ;;
        -d|--debug)
            emcmake cmake . -DCMAKE_BUILD_TYPE=Debug
            echo "Building for debug"
            ;;
    esac
    shift
done

emmake make index


echo "Copying files to /test"
cp -R target/. test/

echo "Done."