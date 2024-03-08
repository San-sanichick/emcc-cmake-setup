cmake_minimum_required(VERSION 3.0.0)
project(helloworld)

add_definitions(-std=c++20)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)

file(GLOB_RECURSE CORE_SRC src/*.cpp)

add_executable(index ${CORE_SRC})

# add local includes
target_include_directories(index PUBLIC include)

# add libs
target_include_directories(index PUBLIC vendors/simple-cpp-logger/include)

# define DEBUG_BUILD macro
target_compile_definitions(index PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)
# make paths relative
target_compile_options(index PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")

if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX .js)

    # set base link flags
    set_property(TARGET index PROPERTY LINK_FLAGS "-lembind -sMODULARIZE=1 -sEXPORT_ES6=1 --bind ")
    
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-O3 -g0")
    elseif (CMAKE_BUILD_TYPE STREQUAL Debug)
        set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-g3 -sASSERTIONS=2 --memoryprofiler")
    endif()
endif()
