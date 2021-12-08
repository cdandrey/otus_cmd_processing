
cmake_minimum_required(VERSION 3.2)

set(this cmd_processing)
set(sources main.cpp)
set(libs libcmd)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${this} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${this} VERSION 0.0.1)
endif()

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
)

target_link_libraries(
        ${this}
        ${libs}
)

if (MSVC)

    target_compile_options(
        ${this}
        PRIVATE
        /W4
    )

else()

    target_compile_options(
        ${this}
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()

install(TARGETS ${this} RUNTIME DESTINATION bin)


