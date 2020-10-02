
# lib cmd_prcsg

cmake_minimum_required(VERSION 3.2)

set(THIS libcmd_prcsg)
set(HEADERS cmd_processing.h cmd_handler.h)
set(SOURCES cmd_processing.cpp cmd_handler.cpp)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} VERSION 0.0.1)
endif()

add_library(${THIS} ${HEADERS} ${SOURCES})

set_target_properties(
        ${THIS}
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(
        ${THIS}
        PRIVATE
        /W4
    )
else()
    target_compile_options(
        ${THIS}
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

