cmake_minimum_required(VERSION 3.12)

project(
    libataxx
    VERSION 1.0
    DESCRIPTION "A C++ Ataxx library"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
elif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
else()
    message(FATAL_ERROR "Compiler not explicitly supported: ${CMAKE_CXX_COMPILER_ID}" )
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(LIBATAXX_BUILD_EXAMPLES   "whether or not examples should be built" ON)
    option(LIBATAXX_BUILD_TESTS      "whether or not tests should be built" ON)

    if(LIBATAXX_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(LIBATAXX_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
