# project(tvm)

add_library(libtvm SHARED version.cpp)
add_compile_definitions(__LIBTVM)

target_include_directories(libtvm PUBLIC ${CMAKE_CURRENT_BINARY_DIR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(version.hpp.in version.hpp)
