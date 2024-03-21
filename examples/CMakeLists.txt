cmake_minimum_required(VERSION 3.12)

# Project
project(examples VERSION 1.0 LANGUAGES CXX)

# Flags
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC doesn't need -fPIC as it's the default behavior
    # Equivalent of -Wall -Wextra
    add_compile_options(/W3)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fPIC -Wall -Wextra -Wshadow)
else()
    message(FATAL_ERROR "Compiler not explicitly supported: ${CMAKE_CXX_COMPILER_ID}" )
endif()

# TODO not all all applications would want to use libataxx with these flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
else()
    message(FATAL_ERROR "Compiler not explicitly supported: ${CMAKE_CXX_COMPILER_ID}" )
endif ()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add example
add_executable(
    perft
    perft.cpp
)

# Add example
add_executable(
    ttperft
    ttperft.cpp
)

# Add example
add_executable(
    tttperft
    tttperft.cpp
)

# Add example
add_executable(
    pgn
    pgn.cpp
)

# Add example
add_executable(
    benchmark
    benchmark.cpp
)

# Add example
add_executable(
    split
    split.cpp
)

target_link_libraries(perft ataxx_static)
target_link_libraries(ttperft ataxx_static)
target_link_libraries(tttperft ataxx_static)
target_link_libraries(pgn ataxx_static)
target_link_libraries(split ataxx_static)
target_link_libraries(benchmark ataxx_static)
