# project(tvm.spec)

add_executable(
    tvm_spec
    symbol.spec.cpp
    symbol_wildcard.spec.cpp
    tape.spec.cpp
    transition.spec.cpp
    tvm.spec.cpp
    version.spec.cpp
    machine.spec.cpp
)

find_package(doctest REQUIRED)

target_link_libraries(tvm_spec PRIVATE doctest::doctest)
target_link_libraries(tvm_spec PRIVATE libtvm)
