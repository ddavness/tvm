/*
    Symbol wildcards are special symbols that will match with any other symbol.
    Say that W is the wildcard, S1 and S2 are symbols so that S1 != S2, then:

    W == S1 is true
    S1 == W is true

    W == S2 is true
    S2 == W is true

    and the respective negative operators are false.
*/

#include "libtvm/symbol_wildcard.hpp"

#include "libtvm/transition_matchable.hpp"

#include <cstdint>
#include <ostream>

using tvm::symbol_wildcard;
using tvm::transition_matchable;

symbol_wildcard::symbol_wildcard(): transition_matchable(INT32_MAX) {}

std::ostream& tvm::operator<<(std::ostream& to, [[maybe_unused]] const symbol_wildcard& me) {
    to << '*';
    return to;
}

bool symbol_wildcard::operator==([[maybe_unused]] const symbol_wildcard& s) const {
    return true;
}
bool symbol_wildcard::operator!=([[maybe_unused]] const symbol_wildcard& s) const {
    return false;
}

bool symbol_wildcard::omatch([[maybe_unused]] const transition_matchable& m) const {
    return true;
}
bool symbol_wildcard::match([[maybe_unused]] const transition_matchable& m) const {
    return true;
}
