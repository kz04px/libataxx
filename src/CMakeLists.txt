cmake_minimum_required(VERSION 3.12)

# Project
project(Libataxx VERSION 1.0 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC doesn't need -fPIC as it's the default behavior
    # Equivalent of -Wall -Wextra
    add_compile_options(/W3)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fPIC -Wall -Wextra -Wshadow)
else()
    message(FATAL_ERROR "Compiler not explicitly supported: ${CMAKE_CXX_COMPILER_ID}" )
endif()

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

# Compile the source once
add_library(
    objlib
    OBJECT
    calculate_hash.cpp
    count_legal_moves.cpp
    gameover.cpp
    get_fen.cpp
    is_legal_move.cpp
    legal_captures.cpp
    legal_moves.cpp
    legal_noncaptures.cpp
    lookup.cpp
    makemove.cpp
    perft.cpp
    predict_hash.cpp
    set_fen.cpp
)

target_compile_features(objlib PUBLIC cxx_std_20)

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
