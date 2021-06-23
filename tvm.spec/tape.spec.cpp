#include "libtvm/tape.hpp"

#include "libtvm/symbol.hpp"

#include <doctest/doctest.h>
#include <unicode/unistr.h>
#include <vector>

using tvm::symbol;

TEST_SUITE("Manipulating tapes") {
    TEST_CASE("Empty tapes return empty symbols") {
        tvm::tape t;

        CHECK(!t.read());
        t.move(tvm::tape_transition::LEFT);
        CHECK(!t.read());
        t.move(tvm::tape_transition::RIGHT);
        t.move(tvm::tape_transition::RIGHT);
        CHECK(!t.read());
    }

    TEST_CASE("Building tapes from a container") {
        std::vector<symbol> a {symbol('x'),
            symbol('y'),
            symbol(static_cast<UChar32>(U'💻')),
            symbol('_'),
            symbol(static_cast<UChar32>(U'💻'))};

        tvm::tape t(a);
    }
}
