#!/bin/bash

# tput is for fancy printing
# print vars
bold=$(tput bold)
normal=$(tput sgr0)


# activate emscripten variables
export EMSDK_QUIET=1
source ./vendors/emsdk/emsdk_env.sh


# setup and run cmake and make
release=false
debug=false

while [[ $# -gt 0 ]];
do
    case "$1" in
        -r|--release)
            release=true
            ;;
        -d|--debug)
            debug=true
            ;;
    esac
    shift
done

if ([ "$release" = true ] && [ "$debug" = true ]) || ([ "$release" = false ] && [ "$debug" = false ]); then
    echo "What are you doing?"
    exit 126
elif [ "$release" = true ]; then
    echo "${bold}Building for release${normal}"
    tput dim
    emcmake cmake . -DCMAKE_BUILD_TYPE=Release
elif [ "$debug" = true ]; then
    echo "${bold}Building for debug${normal}"
    tput dim
    emcmake cmake . -DCMAKE_BUILD_TYPE=Debug
fi

tput sgr0

# clear target dir
echo "${bold}Clearing /target dir${normal}"
rm -rf target/*


# clear test dir
echo "${bold}Clearing /test dir${normal}"

cd test
GLOBIGNORE=index.html:test.js
rm -rf *
unset GLOBIGNORE
cd ..


# run make
emmake make index


# copy files into test/
echo "${bold}Copying files to /test${normal}"
cp -R target/. test/

echo "${bold}Done.${normal}"