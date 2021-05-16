# project(tvm.spec)

add_executable(tvm_spec tvm.spec.cpp version.spec.cpp symbol.spec.cpp)

find_package(Catch2 REQUIRED)

target_link_libraries(tvm_spec PRIVATE Catch2::Catch2)
target_link_libraries(tvm_spec PRIVATE libtvm)
