/*
    hello
*/

#include "libtvm/symbol.hpp"

const UChar32 BLANK_SYMBOL = '_';

using std::ostream;
using tvm::symbol;

// Public constructors
symbol::symbol(): index(0) {}
symbol::symbol(UChar c): index(c == BLANK_SYMBOL ? 0 : c) {}
symbol::symbol(UChar32 c): index(c == BLANK_SYMBOL ? 0 : c) {}

bool symbol::operator==(const symbol& other) const {
    return index == other.index;
}
bool symbol::operator!=(const symbol& other) const {
    return index != other.index;
}

bool symbol::operator!() const {
    return index == 0;
}

ostream& symbol::operator<<(ostream& to) const {
    return to;
}
