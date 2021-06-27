#include "libtvm/symbol_wildcard.hpp"

#include "libtvm/symbol.hpp"

#include <doctest/doctest.h>

TEST_SUITE("Using symbol wildcards") {
    const tvm::symbol s0;
    const tvm::symbol s1('x');
    const tvm::symbol s2('y');

    const tvm::symbol_wildcard w;

    TEST_CASE("A wildcard matches with a blank symbol") {
        CHECK(s0.match(w));
        CHECK(w.match(s0));
    }

    TEST_CASE("A wildcard matches with any symbol") {
        // Verify that these two symbols are different
        REQUIRE(s1 != s2);

        CHECK(s1.match(w));
        CHECK(w.match(s1));

        CHECK(s2.match(w));
        CHECK(w.match(s2));
    }

    TEST_CASE("A wildcard is equal and matches with itself") {
        CHECK(w == tvm::symbol_wildcard());
        CHECK_FALSE(w != tvm::symbol_wildcard());

        CHECK(w.match(tvm::symbol_wildcard()));
    }
}
