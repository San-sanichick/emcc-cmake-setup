cmake_minimum_required(VERSION 3.0.0)
project(emcc-cmake-setup)

message("Enviroment: ${CMAKE_SYSTEM_NAME}")


add_definitions(-std=c++20 -fexperimental-library)
set(CMAKE_CXX_STANDARD 20)


# set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
# set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")


if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target/wasm)
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target/native)
endif()



file(GLOB_RECURSE CORE_SRC src/*.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    list(FILTER CORE_SRC EXCLUDE REGEX "main.cpp")
else ()
    list(FILTER CORE_SRC EXCLUDE REGEX "emscripten_bindings.cpp")
endif()


# native linux target
add_executable(native ${CORE_SRC})
# wasm target
add_executable(index ${CORE_SRC})



# add local includes
target_include_directories(native PUBLIC include)
target_include_directories(index PUBLIC include)

# !add libs
target_include_directories(native SYSTEM PUBLIC 
    vendors/simple-cpp-logger/include 
)

target_include_directories(index SYSTEM PUBLIC 
    vendors/simple-cpp-logger/include 
    vendors/skia 
    vendors/skia/src
    vendors/skia/include 
    vendors/skia/include/config
    vendors/skia/include/gpu
    vendors/skia/include/core
)

add_subdirectory(vendors/result)

target_link_libraries(
    native PRIVATE 
    Result::Result
)
target_link_libraries(
    index PRIVATE 
    Result::Result 
)
# !end add libs

# ! precompile headers
set(PCH include/math/math_pch.hpp include/pch.hpp)

# target_precompile_headers(native PRIVATE ${PCH})
# target_precompile_headers(index PRIVATE ${PCH})
# ! end precompile



# define DEBUG_BUILD macro
add_compile_definitions($<$<CONFIG:Debug>:DEBUG_BUILD>)

# make paths relative
target_compile_options(native PRIVATE 
    -ffile-prefix-map=${CMAKE_SOURCE_DIR}=.
    -pedantic 
    -Wall 
    -Wextra
    # -Wcast-align 
    # -Wcast-qual 
    # -Wctor-dtor-privacy 
    # -Wformat=2 
    # -Winit-self 
    # -Wlogical-op 
    # -Wmissing-declarations 
    # -Wmissing-include-dirs 
    # -Wnoexcept 
    # -Wold-style-cast 
    # -Woverloaded-virtual 
    # -Wredundant-decls 
    # -Wsign-conversion 
    # -Wsign-promo 
    # -Wstrict-null-sentinel 
    # -Wstrict-overflow=5 
    # -Wundef 
    # -Werror
)
target_compile_options(index PRIVATE 
    # -ffile-prefix-map=${CMAKE_SOURCE_DIR}=.
    -pedantic 
    -Wall 
    -Wextra
)


if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)

    # build this as a js module
    set(CMAKE_EXECUTABLE_SUFFIX .mjs)
    
    target_link_options(index PRIVATE 
        --bind
        -lembind
        -sMODULARIZE=1
        -sEXPORT_ES6=1
        -sNODEJS_CATCH_EXIT=0
        -sMAX_WEBGL_VERSION=2
        -sMIN_WEBGL_VERSION=1
        -sUSE_WEBGL2=1
        -sFULL_ES2
        -sFULL_ES3 
        -flto
        -sALLOW_MEMORY_GROWTH=1
        -sEXPORTED_FUNCTIONS=['_malloc']
        -sEXPORTED_RUNTIME_METHODS=['GL'] 
        ${PROJECT_SOURCE_DIR}/vendors/skia/out/wasm/libskia.a 
        $<$<CONFIG:Release>:-O3 -g0>
        $<$<CONFIG:Debug>:-Og -g3 -sASSERTIONS=2 --memoryprofiler>
    )

else ()
        
    target_link_options(native PRIVATE
        -fno-exceptions
        -fanalyzer
        -flto
        $<$<CONFIG:Release>:-O3 -g0>
        $<$<CONFIG:Debug>:-Og -g3>
    )

endif()
