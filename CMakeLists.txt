cmake_minimum_required(VERSION 3.12)

# Project
project(Libataxx VERSION 1.0 LANGUAGES CXX)

# Base directory relative includes
include_directories(.)
include_directories(./src/)
include_directories(./build/)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add the static library
add_library(
    ataxx-static
    STATIC
    src/count_moves.cpp
    src/gameover.cpp
    src/get_fen.cpp
    src/hash.cpp
    src/legal_captures.cpp
    src/legal_move.cpp
    src/legal_moves.cpp
    src/makemove.cpp
    src/perft.cpp
    src/set_fen.cpp
)

# Add the shared library
add_library(
    ataxx-shared
    SHARED
    src/count_moves.cpp
    src/gameover.cpp
    src/get_fen.cpp
    src/hash.cpp
    src/legal_captures.cpp
    src/legal_move.cpp
    src/legal_moves.cpp
    src/makemove.cpp
    src/perft.cpp
    src/set_fen.cpp
)

# Add the test executable
add_executable(
    libataxx-test
    tests/main.cpp
    tests/count_moves.cpp
    tests/hash.cpp
    tests/passing.cpp
    tests/set_get.cpp
    tests/from_uai.cpp
    tests/legal_captures.cpp
    tests/perft.cpp
    tests/set_turn.cpp
    tests/gameover.cpp
    tests/legal_move.cpp
    tests/reachable.cpp
    tests/square.cpp
    tests/get_fen.cpp
    tests/main.cpp
    tests/score.cpp
    tests/pgn.cpp
    tests/counters.cpp
)

set_target_properties(
    ataxx-static
    PROPERTIES
    OUTPUT_NAME "ataxx"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
)
set_target_properties(
    ataxx-shared
    PROPERTIES
    OUTPUT_NAME "ataxx"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
)

set_property(TARGET libataxx-test PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)

target_link_libraries(libataxx-test ataxx-static)
