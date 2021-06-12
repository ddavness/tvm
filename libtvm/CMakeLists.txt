# project(tvm)

add_library(libtvm SHARED version.cpp symbol.cpp tape.cpp)
add_compile_definitions(__LIBTVM)

configure_file(version.hpp.in version.hpp)

find_package(ICU REQUIRED COMPONENTS uc)

target_link_libraries(libtvm PRIVATE ICU::uc)
