cmake_minimum_required(VERSION 3.0.0)
project(helloworld)

add_definitions(-std=c++20)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

# file(GLOB_RECURSE CORE_SRC src/*.cpp)
file(GLOB_RECURSE CORE_SRC src/math.cpp)

add_executable(index ${CORE_SRC})
# add_library(hello ${CORE_SRC})
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX .js)

    set_target_properties(index PROPERTIES LINK_FLAGS "-O3 -s DEMANGLE_SUPPORT=1 -sMODULARIZE=1 -sEXPORT_ES6=1 --bind")
    # set_target_properties(index PROPERTIES COMPILE_FLAGS "--embind-emit-tsd index.d.ts")
endif()
