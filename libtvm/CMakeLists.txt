# project(tvm)

add_library(
    libtvm SHARED
    # Domain
    machine.cpp
    state.cpp
    symbol.cpp
    symbol_wildcard.cpp
    tape.cpp
    transition.cpp
    transition_matchable.cpp
    version.cpp
    # Builders
    builder/machine_builder.cpp
)

configure_file(version.hpp.in version.hpp)

find_package(ICU REQUIRED COMPONENTS uc)
target_link_libraries(libtvm PRIVATE ICU::uc)
