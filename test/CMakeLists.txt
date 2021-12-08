# test cmd_prcsg

cmake_minimum_required(VERSION 3.2)

set(GTEST_ROOT $ENV{GTEST_LIBRARY_DIR})
set(GTEST_INCLUDE_DIR $ENV{GTEST_INCLUDE_DIR})

message(GTEST_ROOT: ${GTEST_ROOT})
message(GTEST_INCLUDE_DIR: ${GTEST_INCLUDE_DIR})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(this tb_main)
set(sources tb_main.cpp)
set(libs libcmd)

add_executable(${this} ${sources})

set_target_properties(
    ${this}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    ${this}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    ${GTEST_INCLUDE_DIR}
)

target_link_libraries(${this} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${this} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${this} ${libs})

if (MSVC)
    target_compile_options(
        ${this}
        PRIVATE
        /W4
        $<$<CONFIG:Debug>:/MT>
        $<$<CONFIG:Release>:/MT>

    )
else ()
    target_compile_options(
        ${this}
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()

add_test(${this} ${this})
