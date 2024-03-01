cmake_minimum_required(VERSION 3.0.0)
project(helloworld)

add_definitions(-std=c++20)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

file(GLOB_RECURSE CORE_SRC src/*.cpp)

add_executable(index ${CORE_SRC})
target_include_directories(index PUBLIC include)
target_compile_definitions(index PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX .js)

    if (CMAKE_BUILD_TYPE STREQUAL Release)
        set_target_properties(index PROPERTIES LINK_FLAGS "-lembind -O3 -g0 -sMODULARIZE=1 -sEXPORT_ES6=1 --bind --embind-emit-tsd index.d.ts")
    elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
        set_target_properties(index PROPERTIES LINK_FLAGS "-lembind -O3 -g3 -sMODULARIZE=1 -sEXPORT_ES6=1 --bind --embind-emit-tsd index.d.ts")
    endif()

endif()
