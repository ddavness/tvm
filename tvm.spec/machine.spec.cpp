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

    TEST_CASE("Create and run a machine with looping transitions. Wildcards are defined last.") {
        /*
            Machine blueprint is as follows:
            <START> ↺ *,*,R
               ↳ _,_,L ---> <SW> ---> _,_,R ---> <ACCEPT>
                             ↺ A,b,L
                             ↺ b,a,L
                             ↺ a,B,L
                             ↺ B,A,L
                             ↺ *,*,L
        */

        symbol_wildcard w;
        symbol blank;
        symbol abig('A');
        symbol asmol('a');
        symbol bbig('B');
        symbol bsmol('b');

        symbol rocket('r');

        state state_write = state("SW");

        machine_builder mb("AbaB");

        machine m =
            mb.add_state(state_write)
                .add_transition(mb.start_state(), transition({blank}, {blank}, {tape_transition::LEFT}), state_write)
                .add_transition(mb.start_state(), transition({w}, {w}, {tape_transition::RIGHT}), mb.start_state())
                .add_transition(state_write, transition({abig}, {bsmol}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({bsmol}, {asmol}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({asmol}, {bbig}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({bbig}, {abig}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({blank}, {blank}, {tape_transition::RIGHT}), mb.accept_state())
                .add_transition(state_write, transition({w}, {w}, {tape_transition::LEFT}), state_write)
                .finalize();

        tape t({rocket, abig, asmol, rocket, bbig, bsmol, bsmol});
        machine_instance exec = m.fork({t});

        exec.run();

        t = exec.tapes().at(0);
        CHECK(t.read() == rocket);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == bsmol);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == bbig);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == rocket);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == abig);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == asmol);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == asmol);
    }

    TEST_CASE("Create and run a machine with looping transitions. Wildcards are defined first.") {
        /*
            Machine blueprint is as follows:
            <START> ↺ *,*,R
               ↳ _,_,L ---> <SW> ---> _,_,R ---> <ACCEPT>
                             ↺ *,0,L
        */

        symbol_wildcard w;
        symbol blank;
        symbol clean('0');
        symbol gar('1');
        symbol ba('2');
        symbol ge('3');

        state state_write = state("SW");

        machine_builder mb("garbage");

        machine m =
            mb.add_state(state_write)
                .add_transition(mb.start_state(), transition({w}, {w}, {tape_transition::RIGHT}), mb.start_state())
                .add_transition(mb.start_state(), transition({blank}, {blank}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({w}, {clean}, {tape_transition::LEFT}), state_write)
                .add_transition(state_write, transition({blank}, {blank}, {tape_transition::RIGHT}), mb.accept_state())
                .finalize();

        tape t({gar, ba, ge, gar, ge, ba});

        machine_instance exec = m.fork({t});

        exec.run();

        t = exec.tapes().at(0);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == clean);
        t.move(tape_transition::RIGHT);
        CHECK(t.read() == blank);
    }

    TEST_CASE("Makes sure that for any machine, only one (state_from, transition_expect) pair exists.") {
        /*
            Machine blueprint is as follows:
            <START> ↺ *,0,R
               ↳ *,1,R ---> <ACCEPT>
        */

        symbol_wildcard w;
        symbol blank;
        symbol zero('0');
        symbol one('1');

        machine_builder mb("np");
        REQUIRE_THROWS_WITH(
            [&]() {
                machine m = mb.add_transition(mb.start_state(),
                                  transition({w}, {w}, {tape_transition::RIGHT}),
                                  mb.accept_state())
                                .add_transition(mb.start_state(),
                                    transition({w}, {w}, {tape_transition::RIGHT}),
                                    mb.accept_state())
                                .finalize();
            }(),
            "Non-deterministic code is not supported!");
    }
}
