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
    combined_moves.cpp
    count_legal_moves.cpp
    counters.cpp
    from_uai.cpp
    get_fen.cpp
    get_hash.cpp
    is_gameover.cpp
    is_legal_move.cpp
    legal_captures.cpp
    legal_noncaptures.cpp
    main.cpp
    move.cpp
    passing.cpp
    perft.cpp
    pgn.cpp
    reachable.cpp
    result.cpp
    score.cpp
    set_get.cpp
    set_turn.cpp
    square.cpp
    transformations.cpp
)

target_link_libraries(tests ataxx_static)
