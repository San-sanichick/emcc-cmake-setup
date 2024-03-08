#!/bin/bash

# tput is for fancy printing
# print vars
bold=$(tput bold)
normal=$(tput sgr0)

help()
{
    echo "Build this project with CMAKE."
    echo
    echo "Syntax: build.sh -r|d [-c] [-n]"
    echo "options:"
    echo "r|release     Build for release."
    echo "d|debug       Build for debug."
    echo "c|clean       Clean CMAKE cache files."
    echo "n|native      Build native Linux binary."
}

# setup and run cmake and make
release=false
debug=false
clean=false
native=false

while [[ $# -gt 0 ]];
do
    case "$1" in
        -r|--release)
            release=true
            ;;
        -d|--debug)
            debug=true
            ;;
        -c|--clean)
            clean=true
            ;;
        -n|--native)
            native=true
            ;;
        \?|-h|--help)
            help
            exit 1
            ;;
    esac
    shift
done

if [ "${clean}" = true ]; then
    echo "${bold}Clearing CMAKE files...${normal}"
    rm -rf build
    rm -rf CMakeFiles
    rm -f cmake_install.cmake
    rm -f CMakeCache.txt
    rm -f Makefile
    echo "${bold}Cleared${normal}"

    if [ "$release" = false ] && [ "$debug" = false ]; then
        exit 1
    fi
fi

if  [ "$native" = false ]; then
    # activate emscripten variables
    export EMSDK_QUIET=1
    source ./vendors/emsdk/emsdk_env.sh
fi

if ([ "$release" = true ] && [ "$debug" = true ]) || ([ "$release" = false ] && [ "$debug" = false ]); then
    echo "Incorrect flags set"
    exit 126

elif [ "$native" = true ] && [ "$release" = true ]; then
    echo "${bold}Building for release${normal}"
    tput dim
    cmake . -DCMAKE_BUILD_TYPE=Release
elif [ "$native" = true ] && [ "$debug" = true ]; then
    echo "${bold}Building for debug${normal}"
    tput dim
    cmake . -DCMAKE_BUILD_TYPE=Debug

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

tput sgr0

# run make
if [ "$native" = true ]; then
    make index
else
    emmake make index
fi

if [ "$native" = false ]; then
    # copy files into test/
    echo "${bold}Copying files to /test${normal}"
    cp -R target/. test/
fi

echo "${bold}Done.${normal}"