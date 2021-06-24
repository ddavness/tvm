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

    const std::vector<symbol> container {symbol('x'),
        symbol('y'),
        symbol(static_cast<UChar32>(U'💻')),
        symbol('_'),
        symbol(static_cast<UChar32>(U'💻'))};

    TEST_CASE("Tapes can be created from a container") {
        tvm::tape t(container);

        CHECK(t.read() == container.at(0));
        t.move(tvm::tape_transition::LEFT);
        CHECK(!t.read());
        t.move(tvm::tape_transition::RIGHT);
        CHECK(t.read() == container.at(0));
        t.move(tvm::tape_transition::RIGHT);
        CHECK(t.read() == container.at(1));
    }

    TEST_CASE("The needle position can be set when creating a tape") {
        tvm::tape t(container, 4);

        CHECK(t.read() == container.at(4));
        t.move(tvm::tape_transition::LEFT);
        CHECK(t.read() == container.at(3));
        t.move(tvm::tape_transition::LEFT);
        CHECK(t.read() == container.at(4));
    }

    TEST_CASE("After moving the needle with the STAY transition, the symbol read is the same") {
        const symbol s('@');
        tvm::tape t({s});

        CHECK(t.read() == s);
        t.move(tvm::tape_transition::STAY);
        CHECK(t.read() == s);
    }

    TEST_CASE("Write a symbol, then read it") {
        tvm::tape t;
        symbol s('$');

        t.write(s);
        CHECK(t.read() == s);
    }
}
