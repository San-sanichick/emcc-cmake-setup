#!/bin/bash

# tput is for fancy printing
# print vars
bold=$(tput bold)
normal=$(tput sgr0)


echo "${bold}Clearing CMAKE files...${normal}"
rm -rf build # uhh this may be redundant
rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f CMakeCache.txt
rm -f Makefile
echo "${bold}Cleared${normal}"