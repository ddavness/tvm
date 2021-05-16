# project(tvm)

add_library(libtvm SHARED version.cpp symbol.cpp)
add_compile_definitions(__LIBTVM)

configure_file(version.hpp.in version.hpp)

find_package(ICU REQUIRED COMPONENTS uc io)

target_link_libraries(libtvm PRIVATE ICU::uc ICU::io)
