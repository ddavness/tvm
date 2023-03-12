#include "libtvm/symbol.hpp"
#include "libtvm/tape.hpp"

#include <doctest/doctest.h>
#include <unicode/unistr.h>
#include <vector>

using tvm::symbol;

TEST_SUITE("03 - Manipulating tapes") {
    const symbol blank;

    TEST_CASE("03.01 - Empty tapes return empty symbols") {
        tvm::tape t;

        CHECK(!t.read());
        CHECK(t.read() == blank);
        t.move(tvm::tape_transition::LEFT);
        CHECK(!t.read());
        CHECK(t.read() == blank);
        t.move(tvm::tape_transition::RIGHT);
        t.move(tvm::tape_transition::RIGHT);
        CHECK(!t.read());
        CHECK(t.read() == blank);
    }

    const std::vector<symbol> container {symbol('x'),
        symbol('y'),
        symbol(static_cast<UChar32>(U'🍬')),
        symbol('_'),
        symbol(static_cast<UChar32>(U'💻'))};

    TEST_CASE("03.02 - Tapes can be created from a container") {
        tvm::tape t(container);

        CHECK(t.read() == container.at(0));
        t.move(tvm::tape_transition::LEFT);
        CHECK(!t.read());
        t.move(tvm::tape_transition::RIGHT);
        CHECK(t.read() == container.at(0));
        t.move(tvm::tape_transition::RIGHT);
        CHECK(t.read() == container.at(1));
    }

    TEST_CASE("03.03 - The needle position can be set when creating a tape") {
        tvm::tape t(container, 4);

        CHECK(t.read() == container.at(4));
        t.move(tvm::tape_transition::LEFT);
        CHECK(t.read() == container.at(3));
        t.move(tvm::tape_transition::LEFT);
        CHECK(t.read() == container.at(2));
    }

    TEST_CASE("03.04 - After moving the needle with the STAY transition, the symbol read is the same") {
        const symbol s('@');
        tvm::tape t({s});

        CHECK(t.read() == s);
        t.move(tvm::tape_transition::STAY);
        CHECK(t.read() == s);
    }

    TEST_CASE("03.05 - Write a symbol, then read it") {
        tvm::tape t;
        symbol s('$');

        t.write(s);
        CHECK(t.read() == s);
    }
}
