
cmake_minimum_required(VERSION 3.2)

set (this CommandProcessing)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${this} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${this} 
            VERSION 0.0.1)
endif()

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

