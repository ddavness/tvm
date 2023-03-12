#include "libtvm/symbol.hpp"
#include "libtvm/symbol_wildcard.hpp"
#include "libtvm/tape.hpp"
#include "libtvm/transition.hpp"

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

TEST_SUITE("04 - State transitions") {
    const symbol x('a'), y('b'), z('@');
    const tvm::symbol_wildcard wc;

    TEST_CASE("04.01 - Transitions with one tape") {
        transition t({y}, {z}, {tape_transition::STAY});
        vector<tape> t1({tape({x})});
        vector<tape> t2({tape({y})});

        CHECK(!t.match_and_run({t1}));
        CHECK(t1.at(0).read() == x);

        CHECK(t.match_and_run({t2}));
        CHECK(t2.at(0).read() == z);
    }

    TEST_CASE("04.02 - Transitions matching more than one tape") {
        transition t({x, y, y}, {z, z, z}, {tape_transition::STAY, tape_transition::STAY, tape_transition::STAY});
        vector<tape> tt({tape({x}), tape({y}), tape({y})});

        CHECK(t.match_and_run(tt));

        CHECK(tt.at(0).read() == z);
        CHECK(tt.at(1).read() == z);
        CHECK(tt.at(2).read() == z);
    }

    TEST_CASE("04.03 - Transitons do not run if not all tapes match") {
        transition t({x, y, z}, {z, x, y}, {tape_transition::LEFT, tape_transition::RIGHT, tape_transition::LEFT});
        vector<tape> tt({tape({x}), tape({y}), tape({y})});
        tape t1({x});
        tape t2({y});
        tape t3({y});

        CHECK(!t.match_and_run(tt));

        CHECK(tt.at(0).read() == x);
        CHECK(tt.at(1).read() == y);
        CHECK(tt.at(2).read() == y);
    }

    TEST_CASE("04.04 - Wildcards will match with anything") {
        transition t({wc, wc}, {x, x}, {tape_transition::STAY, tape_transition::STAY});
        vector<tape> tt({tape({z}), tape({x})});
        vector<tape> uu({tape({y}), tape({y})});

        CHECK(t.match_and_run(tt));
        CHECK(tt.at(0).read() == x);
        CHECK(tt.at(1).read() == x);

        CHECK(t.match_and_run(uu));
        CHECK(uu.at(0).read() == x);
        CHECK(uu.at(1).read() == x);
    }

    TEST_CASE("04.05 - Wildcard writing") {
        transition t({wc}, {wc}, {tape_transition::RIGHT});
        vector<tape> tt({tape({x, y})});

        CHECK(t.match_and_run(tt));
        CHECK(tt.at(0).read() == y);
        tt.at(0).move(tape_transition::LEFT);
        CHECK(tt.at(0).read() == x);
    }
}
