# project(tvm.spec)

add_executable(
    tvm_spec
    00-version.spec.cpp
    01-symbol.spec.cpp
    02-symbol_wildcard.spec.cpp
    03-tape.spec.cpp
    04-transition.spec.cpp
    05-machine.spec.cpp
    tvm.spec.cpp
)

find_package(ICU REQUIRED COMPONENTS uc)
find_package(doctest REQUIRED)

target_link_libraries(tvm_spec PRIVATE doctest::doctest)
target_link_libraries(tvm_spec PRIVATE ICU::uc)
target_link_libraries(tvm_spec PRIVATE libtvm)

