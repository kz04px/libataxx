cmake_minimum_required(VERSION 3.12)

# Project
project(tests VERSION 1.0 LANGUAGES CXX)

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

# Add the test executable
add_executable(
    tests
    main.cpp
    count_moves.cpp
    combined_moves.cpp
    hash.cpp
    passing.cpp
    set_get.cpp
    from_uai.cpp
    is_gameover.cpp
    legal_captures.cpp
    legal_noncaptures.cpp
    perft.cpp
    set_turn.cpp
    legal_move.cpp
    move.cpp
    reachable.cpp
    result.cpp
    square.cpp
    get_fen.cpp
    main.cpp
    score.cpp
    pgn.cpp
    counters.cpp
    transformations.cpp
)

target_link_libraries(tests ataxx_static)
