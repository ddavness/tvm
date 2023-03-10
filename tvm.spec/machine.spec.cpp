#include "libtvm/machine.hpp"

#include "libtvm/builder/machine_builder.hpp"
#include "libtvm/state.hpp"
#include "libtvm/symbol.hpp"
#include "libtvm/symbol_wildcard.hpp"
#include "libtvm/tape.hpp"
#include "libtvm/transition.hpp"

#include <doctest/doctest.h>

using tvm::machine;
using tvm::machine_instance;
using tvm::state;
using tvm::symbol;
using tvm::symbol_wildcard;
using tvm::tape;
using tvm::tape_transition;
using tvm::transition;

using tvm::builder::machine_builder;

TEST_SUITE("Building Turing Machines") {
    TEST_CASE("Build an empty machine") {
        symbol_wildcard w;
        transition stay({w}, {w}, {tape_transition::STAY});
        machine_builder mb("basic");

        const machine& mach = mb.add_transition(mb.start_state(), stay, mb.accept_state()).finalize();

        CHECK(mach.start() == mb.start_state());
    }

    TEST_CASE("Create and run a machine with two states between start and finish") {
        /*
            Machine blueprint is as follows:
            <START> ---> *,1,R ---> <S1> ---> *,0,R ---> <S2> ---> *,1,S ---> <ACCEPT>
        */

        symbol_wildcard w;
        symbol zero('0');
        symbol one('1');

        state s1 = state("S1");
        state s2 = state("S2");

        machine_builder mb("101");

        machine m = mb.add_state(s1)
                        .add_state(s2)
                        .add_transition(mb.start_state(), transition({w}, {one}, {tape_transition::RIGHT}), s1)
                        .add_transition(s1, transition({w}, {zero}, {tape_transition::RIGHT}), s2)
                        .add_transition(s2, transition({w}, {one}, {tape_transition::STAY}), mb.accept_state())
                        .finalize();

        machine_instance exec = m.fork();

        exec.run();
        tape t = exec.tapes().at(0);

        CHECK(t.read() == one);
        t.move(tape_transition::LEFT);
        CHECK(t.read() == zero);
        t.move(tape_transition::LEFT);
        CHECK(t.read() == one);
    }
}
