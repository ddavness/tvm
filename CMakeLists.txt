cmake_minimum_required(VERSION 3.13.0) # Version distributed by Debian Buster (10.x, stable)

# Place everything in one place so that shared libraries are easily obtained
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# We'll be using vcpkg to get any libraries we may need
# Look for either VCPKG_INSTALLATION_ROOT or VCPKG_ROOT or VCPKG env variables
if(EXISTS $ENV{VCPKG})
    set(VCPKG $ENV{VCPKG})
elseif(EXISTS $ENV{VCPKG_ROOT})
    set(VCPKG $ENV{VCPKG_ROOT})
elseif(EXISTS $ENV{VCPKG_INSTALLATION_ROOT})
    set(VCPKG $ENV{VCPKG_INSTALLATION_ROOT})
else()
    message(FATAL_ERROR "Couldn't find vcpkg anywhere! Please make sure that AT LEAST ONE of these environment variables is set:
    VCPKG or VCPKG_ROOT or VCPKG_INSTALLATION_ROOT")
endif()

message( STATUS "Found vcpkg at ${VCPKG}" )
set(CMAKE_TOOLCHAIN_FILE "${VCPKG}/scripts/buildsystems/vcpkg.cmake")

# Turing Virtual Machine
project(tvm VERSION 0.0.1)

# Don't mess with output names. No weird prefixes, please!
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# Set the C++ standard. We'll be using C++17 as it's the most recent standard (while still being stable)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make the compiler harsher on errors
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# Make header files available for all the projects in this repo
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

add_subdirectory(libtvm)

option(BUILD_TESTS "Also compile test executables" OFF)
if(BUILD_TESTS)
    message(STATUS "Adding the tests to be built.")
    add_subdirectory(tvm.spec)
endif()
