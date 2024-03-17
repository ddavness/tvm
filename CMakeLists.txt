cmake_minimum_required(VERSION 3.13.0) # Version distributed by Debian Buster (10.x, stable)

option(WITH_VCPKG "Use vcpkg" OFF)
option(WITH_TESTS "Also compile test executables" OFF)
option(WITH_COVERAGE "Also add test coverage information" OFF)

# Place everything in one place so that shared libraries are easily obtained
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Don't discriminate by build type - that makes our output folders less consistent cross-platform-wise
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(WITH_VCPKG)
    message(STATUS " * Building with vcpkg.")
    # Look for either VCPKG_INSTALLATION_ROOT or VCPKG_ROOT or VCPKG env variables
    if(EXISTS $ENV{VCPKG})
        set(VCPKG $ENV{VCPKG})
    elseif(EXISTS $ENV{VCPKG_ROOT})
        set(VCPKG $ENV{VCPKG_ROOT})
    elseif(EXISTS $ENV{VCPKG_INSTALLATION_ROOT})
        set(VCPKG $ENV{VCPKG_INSTALLATION_ROOT})
    elseif(EXISTS ./vcpkg)
        set(VCPKG ./vcpkg)
    else()
        message(
            FATAL_ERROR
    "Couldn't find vcpkg anywhere! Please make sure that AT LEAST ONE of these environment variables is set:
        VCPKG or VCPKG_ROOT or VCPKG_INSTALLATION_ROOT
        
    Or, clone the vcpkg repository inside this one:
        git clone --depth 1 https://github.com/microsoft/vcpkg"
        )
    endif()

    message(STATUS "Found vcpkg at ${VCPKG}")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG}/scripts/buildsystems/vcpkg.cmake")

    # Export the vcpkg include
    find_path(VCPKG_INCLUDE include)
    include_directories(${VCPKG_INCLUDE}/include)

endif()

# Turing Virtual Machine
project(tvm VERSION 0.0.3)

list(APPEND CMAKE_MODULE_PATH "./cmake-modules")

# Don't mess with output names. No weird prefixes, please!
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# Set the C++ standard. We'll be using C++17 as it's the most recent standard (while still being stable)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /WX /source-charset:utf-8)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# Make header files available for all the projects in this repo
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

add_subdirectory(libtvm)

if(WITH_TESTS)
    message(STATUS " * Adding the tests to the build pipeline")
    add_subdirectory(tvm.spec)
endif()

if(WITH_COVERAGE)
    if(WITH_TESTS)
        message(STATUS " * Setting up coverage information")
        include(CodeCoverage)
        append_coverage_compiler_flags_to_target(libtvm)
        setup_target_for_coverage_lcov(
            NAME coverage
            EXECUTABLE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tvm_spec
            DEPENDENCIES tvm_spec
            BASE_DIRECTORY "."
            LCOV_ARGS "--no-external"
        )
        add_compile_options(-O0)
    else()
        message(WARNING " * WITH_COVERAGE was set, but WITH_TESTS was not. Skipping coverage step")
    endif()
endif()
