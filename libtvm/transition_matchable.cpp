/*
    A transition-matchable is a representation (i.e. superclass) for symbols.

    It exists because tvm supports wildcards on transitions. As such you can use either
    symbols or wildcards in transitions. This superclass is essentially for architectural
    purposes only.

    This is - you shouldn't create a transition_matchable directly.
*/

#include "libtvm/transition_matchable.hpp"

using tvm::transition_matchable;

transition_matchable::transition_matchable(int32_t index): idx(index) {}

int32_t transition_matchable::index() const {
    return idx;
}
