cmake_minimum_required(VERSION 3.12)

# Project
project(Libataxx VERSION 1.0 LANGUAGES CXX)

find_package(Threads)

# Base directory relative includes
include_directories(.)
include_directories(./src/)
include_directories(./build/)

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

# Add the static library
add_library(
    static
    STATIC
    src/count_moves.cpp
    src/gameover.cpp
    src/get_fen.cpp
    src/hash.cpp
    src/legal_captures.cpp
    src/legal_move.cpp
    src/legal_moves.cpp
    src/legal_noncaptures.cpp
    src/makemove.cpp
    src/perft.cpp
    src/predict_hash.cpp
    src/set_fen.cpp
)

# Add the shared library
add_library(
    shared
    SHARED
    src/count_moves.cpp
    src/gameover.cpp
    src/get_fen.cpp
    src/hash.cpp
    src/legal_captures.cpp
    src/legal_move.cpp
    src/legal_moves.cpp
    src/legal_noncaptures.cpp
    src/makemove.cpp
    src/perft.cpp
    src/predict_hash.cpp
    src/set_fen.cpp
)

# Add the test executable
add_executable(
    tests
    tests/main.cpp
    tests/count_moves.cpp
    tests/combined_moves.cpp
    tests/hash.cpp
    tests/passing.cpp
    tests/set_get.cpp
    tests/from_uai.cpp
    tests/legal_captures.cpp
    tests/legal_noncaptures.cpp
    tests/perft.cpp
    tests/set_turn.cpp
    tests/gameover.cpp
    tests/legal_move.cpp
    tests/move.cpp
    tests/reachable.cpp
    tests/result.cpp
    tests/square.cpp
    tests/get_fen.cpp
    tests/main.cpp
    tests/score.cpp
    tests/pgn.cpp
    tests/counters.cpp
    tests/transformations.cpp
)

# Add example
add_executable(
    perft
    examples/perft.cpp
)

# Add example
add_executable(
    ttperft
    examples/ttperft.cpp
)

# Add example
add_executable(
    tttperft
    examples/tttperft.cpp
)

# Add example
add_executable(
    pgn
    examples/pgn.cpp
)

# Add example
add_executable(
    split
    examples/split.cpp
)

ADD_CUSTOM_TARGET(examples)

ADD_DEPENDENCIES(
    examples
    perft
    ttperft
    tttperft
    pgn
    split
)

set_target_properties(
    static
    PROPERTIES
    OUTPUT_NAME "ataxx"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static"
)

set_target_properties(
    shared
    PROPERTIES
    OUTPUT_NAME "ataxx"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared"
)

set_target_properties(
    perft
    PROPERTIES
    OUTPUT_NAME "perft"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

set_target_properties(
    ttperft
    PROPERTIES
    OUTPUT_NAME "ttperft"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

set_target_properties(
    tttperft
    PROPERTIES
    OUTPUT_NAME "tttperft"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

set_target_properties(
    pgn
    PROPERTIES
    OUTPUT_NAME "pgn"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

set_target_properties(
    split
    PROPERTIES
    OUTPUT_NAME "split"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

set_property(TARGET tests PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE FALSE)

target_link_libraries(tests static)
target_link_libraries(perft static)
target_link_libraries(ttperft static)
target_link_libraries(tttperft static)
target_link_libraries(pgn static)
target_link_libraries(split static)
