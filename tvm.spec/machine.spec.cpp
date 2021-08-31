#include "libtvm/machine.hpp"

#include "libtvm/builder/machine_builder.hpp"
#include "libtvm/symbol_wildcard.hpp"
#include "libtvm/transition.hpp"

#include <doctest/doctest.h>

TEST_SUITE("Building Turing Machines") {
    TEST_CASE("Build an empty machine") {
        tvm::symbol_wildcard w;
        tvm::transition stay({w}, {w}, {tvm::tape_transition::STAY});
        tvm::builder::machine_builder mb("basic");

        const tvm::machine& mach = mb.add_transition(mb.start_state(), stay, mb.accept_state()).finalize();

        CHECK(mach.start() == mb.start_state());
    }
}
