cmake_minimum_required(VERSION 3.0.0)
project(helloworld)

add_definitions(-std=c++20)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

file(GLOB_RECURSE CORE_SRC src/*.cpp)

add_executable(hello ${CORE_SRC})
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX .html)

    # set_target_properties(hello PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM")
endif()
