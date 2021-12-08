
# root CommandProcessing

cmake_minimum_required(VERSION 3.2)

set (THIS prj_CommandProcessing)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} 
            VERSION 0.0.1)
endif()

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

