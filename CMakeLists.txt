cmake_minimum_required(VERSION 3.12)

project(
    libataxx
    VERSION 1.0
    DESCRIPTION "A C++ Ataxx library"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
