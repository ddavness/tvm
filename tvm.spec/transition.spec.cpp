#include "libtvm/transition.hpp"

#include "libtvm/symbol.hpp"
#include "libtvm/symbol_wildcard.hpp"
#include "libtvm/tape.hpp"

#include <doctest/doctest.h>
#include <unicode/unistr.h>
#include <functional>
#include <vector>

using std::ref;
using std::reference_wrapper;
using std::vector;

using tvm::symbol;
using tvm::tape;
using tvm::tape_transition;
using tvm::transition;

TEST_SUITE("State transitions") {
    const symbol x('a'), y('b'), z('@');
    const tvm::symbol_wildcard wc;

    TEST_CASE("Transitions with one tape") {
        transition t({y}, {z}, {tape_transition::STAY});
        tape t1({x});
        tape t2({y});

        CHECK(!t.match_and_run({t1}));
        CHECK(t1.read() == x);

        CHECK(t.match_and_run({t2}));
        CHECK(t2.read() == z);
    }

    TEST_CASE("Transitions matching more than one tape") {
        transition t({x, y, y}, {z, z, z}, {tape_transition::STAY, tape_transition::STAY, tape_transition::STAY});
        tape t1({x});
        tape t2({y});
        tape t3({y});

        CHECK(t.match_and_run({t1, t2, t3}));

        CHECK(t1.read() == z);
        CHECK(t2.read() == z);
        CHECK(t3.read() == z);
    }

    TEST_CASE("Transitons do not run if not all tapes match") {
        transition t({x, y, z}, {z, x, y}, {tape_transition::LEFT, tape_transition::RIGHT, tape_transition::LEFT});
        tape t1({x});
        tape t2({y});
        tape t3({y});

        CHECK(!t.match_and_run({t1, t2, t3}));

        CHECK(t1.read() == x);
        CHECK(t2.read() == y);
        CHECK(t3.read() == y);
    }

    TEST_CASE("Wildcards will match with anything") {
        transition t({wc, wc}, {x, x}, {tape_transition::STAY, tape_transition::STAY});
        tape t1({z});
        tape t2({x});
        tape u1({y});
        tape u2({y});

        CHECK(t.match_and_run({t1, t2}));
        CHECK(t1.read() == x);
        CHECK(t2.read() == x);

        CHECK(t.match_and_run({u1, u2}));
        CHECK(u1.read() == x);
        CHECK(u2.read() == x);
    }
}
