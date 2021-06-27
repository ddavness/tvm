#include "libtvm/symbol.hpp"

#include <doctest/doctest.h>
#include <unicode/unistr.h>
#include <iostream>
#include <string>

TEST_SUITE("Manipulating symbols") {
    const UChar blank = '_';

    TEST_CASE("Blank symbol semantics are correct") {
        tvm::symbol sym0;

        SUBCASE("An unitialized symbol is blank") {
            CHECK(!sym0);
        }
        SUBCASE("A blank symbol is equal to another blank symbol") {
            CHECK(sym0 == tvm::symbol());
            CHECK(sym0 == tvm::symbol(blank));
        }

        SUBCASE("Copying semantics on blank symbols") {
            tvm::symbol sym00 = sym0;

            THEN("The new symbol is also blank") {
                CHECK(sym0 == sym00);
            }
            AND_THEN("Both symbols are not the same") {
                CHECK(&sym0 != &sym00);
            }
        }
    }

    const UChar ascii = 'x';
    const UChar cyrillic = u'Д';
    const UChar japanese = u'ツ';
    const UChar32 emoji = U'🚀';

    TEST_CASE("General symbol semantics") {
        tvm::symbol sym0(blank);
        tvm::symbol sym1(ascii);
        tvm::symbol sym2(cyrillic);
        tvm::symbol sym3(japanese);
        tvm::symbol sym4(emoji);

        SUBCASE("Symbols are all different from eachother") {
            CHECK(sym0 != sym1);
            CHECK(sym0 != sym2);
            CHECK(sym0 != sym3);
            CHECK(sym0 != sym4);

            CHECK(sym1 != sym2);
            CHECK(sym1 != sym3);
            CHECK(sym1 != sym4);

            CHECK(sym2 != sym3);
            CHECK(sym2 != sym4);

            CHECK(sym3 != sym4);
        }
        SUBCASE("Only sym0 is blank") {
            CHECK(!sym0);

            CHECK(!!sym1);
            CHECK(!!sym2);
            CHECK(!!sym3);
            CHECK(!!sym4);
        }

        SUBCASE("Copying semantics") {
            tvm::symbol copy0 = sym0;
            tvm::symbol copy1 = sym1;
            tvm::symbol copy2 = sym2;
            tvm::symbol copy3 = sym3;
            tvm::symbol copy4 = sym4;

            SUBCASE("The copies are equal to their original symbols") {
                CHECK(sym0 == copy0);
                CHECK(sym1 == copy1);
                CHECK(sym2 == copy2);
                CHECK(sym3 == copy3);
                CHECK(sym4 == copy4);
            }
            SUBCASE("The originals and the copies are not the same symbol") {
                CHECK(&sym0 != &copy0);
                CHECK(&sym1 != &copy1);
                CHECK(&sym2 != &copy2);
                CHECK(&sym3 != &copy3);
                CHECK(&sym4 != &copy4);
            }
        }
    }

    TEST_CASE("Symbol matching") {
        tvm::symbol s0;
        tvm::symbol s1(ascii);
        tvm::symbol s2(emoji);

        SUBCASE("Symbols match with themselves") {
            CHECK(s0.match(s0));
            CHECK(s1.match(s1));
            CHECK(s2.match(s2));
        }

        SUBCASE("Symbols do not match with different symbols") {
            CHECK(!s0.match(s1));
            CHECK(!s1.match(s2));
            CHECK(!s2.match(s0));
        }
    }
}
