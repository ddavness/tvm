cmake_minimum_required(VERSION 3.13.0) # Version distributed by Debian Buster (10.x, stable)

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

project(tvm VERSION 0.0.1)

add_subdirectory(libtvm)
