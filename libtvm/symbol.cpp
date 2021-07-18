/*
    The symbol is the elementar unit of information in Computer Theory.
    In a turing machine, the memory tape can theoretically hold an arbitrary set of different symbols.

    This set can (theoretically) be infinite, but for the sake of this experiment, we're going to
    limit to the 24-bit space. That gives us enough space to hold all different unicode character
    combinations (around 1.1 million at the time of writing) at the same time.

    And honestly, nobody is going to really use that many anyway.
*/

#include "libtvm/symbol.hpp"

#include "libtvm/transition_matchable.hpp"

#include <unicode/unistr.h>
#include <string>

const UChar32 BLANK_SYMBOL = '_';

using std::ostream;
using std::string;

using tvm::symbol;
using tvm::transition_matchable;

// Public constructors
symbol::symbol(): tvm::transition_matchable(0) {}
symbol::symbol(UChar c): tvm::transition_matchable(c == BLANK_SYMBOL ? 0 : c) {}
symbol::symbol(UChar32 c): tvm::transition_matchable(c == BLANK_SYMBOL ? 0 : c) {}
symbol::symbol(const transition_matchable& t): tvm::transition_matchable(t.index()) {}

bool symbol::operator==(const symbol& other) const {
    return index() == other.index();
}
bool symbol::operator!=(const symbol& other) const {
    return index() != other.index();
}

bool symbol::match(const symbol& s) const {
    return index() == s.index();
}
bool symbol::match(const transition_matchable& s) const {
    return s.match(*this);
}

bool symbol::operator!() const {
    return index() == 0;
}

ostream& tvm::operator<<(ostream& to, const symbol& me) {
    string t;
    if (me.index() == 0) {
        to << icu::UnicodeString(BLANK_SYMBOL).toUTF8String(t);
    } else {
        to << icu::UnicodeString(me.index()).toUTF8String(t);
    }

    return to;
}
