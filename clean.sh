#!/bin/bash

echo "${bold}Clearing CMAKE files...${normal}"
rm -rf build
rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f CMakeCache.txt
rm -f Makefile
echo "${bold}Cleared${normal}"