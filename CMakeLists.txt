cmake_minimum_required(VERSION 3.0.0)
project(helloworld)

message("Enviroment: ${CMAKE_SYSTEM_NAME}")


add_definitions(-std=c++20)
set(CMAKE_CXX_STANDARD 20)



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

add_executable(index ${CORE_SRC})



# add local includes
target_include_directories(index PUBLIC include)

# !add libs
target_include_directories(index PUBLIC 
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
    index PRIVATE  
    Result::Result
)
# !end add libs

# define DEBUG_BUILD macro
target_compile_definitions(index PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)
# make paths relative
# target_compile_options(index PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")


target_compile_options(index PRIVATE 
    -ffile-prefix-map=${CMAKE_SOURCE_DIR}=.
    # -pedantic 
    # -Wall 
    # -Wextra 
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

if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)

    set(CMAKE_EXECUTABLE_SUFFIX .mjs)
    
    # set base link flags
    set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-lembind -sMODULARIZE=1 -sEXPORT_ES6=1 --bind ")
    set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-sNODEJS_CATCH_EXIT=0 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=1 -sUSE_WEBGL2=1 -sFULL_ES2 -sFULL_ES3 ")
    set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-sALLOW_MEMORY_GROWTH=1 -sEXPORTED_FUNCTIONS=['_malloc'] -sEXPORTED_RUNTIME_METHODS=['GL'] ")
    set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "vendors/skia/out/wasm/libskia.a ")
    # set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-pthread -sPTHREAD_POOL_SIZE=1 ")
    
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-O3 -g0")
    elseif (CMAKE_BUILD_TYPE STREQUAL Debug)
        set_property(TARGET index APPEND_STRING PROPERTY LINK_FLAGS "-Og -g3 -sASSERTIONS=2 --memoryprofiler")
    endif()
        
else ()
        
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        set_property(TARGET index PROPERTY LINK_FLAGS "-O3 -g0 -fno-exceptions -fmodules-ts")
    elseif (CMAKE_BUILD_TYPE STREQUAL Debug)
        set_property(TARGET index PROPERTY LINK_FLAGS "-Og -g3 -fno-exceptions -fmodules-ts")
    endif()

endif()
