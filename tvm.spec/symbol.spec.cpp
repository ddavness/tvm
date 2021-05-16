#include "libtvm/symbol.hpp"

#include <catch2/catch.hpp>
#include <unicode/unistr.h>
#include <string>

using std::string;
using namespace std::string_literals;

SCENARIO("Manipulating symbols") {
    const UChar blank = '_';
    const UChar ascii = 'x';
    const UChar cyrillic = u'Д';
    const UChar japanese = u'ツ';
    const UChar32 emoji = U'🚀';

    GIVEN("A new blank symbol") {
        tvm::symbol sym0;

        THEN("It is blank") {
            REQUIRE(!sym0);
        }
        AND_THEN("It is equal to another blank symbol") {
            REQUIRE(sym0 == tvm::symbol());
            REQUIRE(sym0 == tvm::symbol(blank));
        }

        WHEN("It is copied") {
            tvm::symbol sym00 = sym0;

            THEN("They're equal") {
                REQUIRE(sym0 == sym00);
            }
            AND_THEN("They're not the same") {
                REQUIRE(&sym0 != &sym00);
            }
        }
    }

    GIVEN("An assortment of symbols") {
        tvm::symbol sym0(blank);
        tvm::symbol sym1(ascii);
        tvm::symbol sym2(cyrillic);
        tvm::symbol sym3(japanese);
        tvm::symbol sym4(emoji);

        THEN("They're all different from eachother") {
            REQUIRE(sym0 != sym1);
            REQUIRE(sym0 != sym2);
            REQUIRE(sym0 != sym3);
            REQUIRE(sym0 != sym4);

            REQUIRE(sym1 != sym2);
            REQUIRE(sym1 != sym3);
            REQUIRE(sym1 != sym4);

            REQUIRE(sym2 != sym3);
            REQUIRE(sym2 != sym4);

            REQUIRE(sym3 != sym4);
        }
        AND_THEN("Only sym0 is blank") {
            REQUIRE(!sym0);

            REQUIRE(!!sym1);
            REQUIRE(!!sym2);
            REQUIRE(!!sym3);
            REQUIRE(!!sym4);
        }

        WHEN("Copies are created") {
            tvm::symbol copy0 = sym0;
            tvm::symbol copy1 = sym1;
            tvm::symbol copy2 = sym2;
            tvm::symbol copy3 = sym3;
            tvm::symbol copy4 = sym4;

            THEN("They're equal") {
                REQUIRE(sym0 == copy0);
                REQUIRE(sym1 == copy1);
                REQUIRE(sym2 == copy2);
                REQUIRE(sym3 == copy3);
                REQUIRE(sym4 == copy4);
            }
            AND_THEN("They're not the same") {
                REQUIRE(&sym0 != &copy0);
                REQUIRE(&sym1 != &copy1);
                REQUIRE(&sym2 != &copy2);
                REQUIRE(&sym3 != &copy3);
                REQUIRE(&sym4 != &copy4);
            }
        }
    }
}
