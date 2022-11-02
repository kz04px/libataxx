cmake_minimum_required(VERSION 3.12)

# Project
project(Libataxx VERSION 1.0 LANGUAGES CXX)

# Flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compile the source once
add_library(
    objlib
    OBJECT
    count_moves.cpp
    gameover.cpp
    get_fen.cpp
    hash.cpp
    is_legal_move.cpp
    legal_captures.cpp
    legal_moves.cpp
    legal_noncaptures.cpp
    makemove.cpp
    perft.cpp
    predict_hash.cpp
    set_fen.cpp
)

# Add the static library
add_library(
    ataxx_static
    STATIC
    $<TARGET_OBJECTS:objlib>
)

# Add the shared library
add_library(
    ataxx_shared
    SHARED
    $<TARGET_OBJECTS:objlib>
)

target_include_directories(
    ataxx_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(
    ataxx_shared
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
