/*
    The transition is used to connect two states together (they may or may not be the same state).
    Transitons are where data processing also happens.

    There are three steps on a transition:

    1. Matching - This is where we determine whether the symbols on the tapes are the ones we expect;
    2. Writing - The symbols in the tape are replaced with the ones in the transition (they may or may not be the same);
    3. Moving - The tape needles are moved according to the transition and the machine moves to the destination state;
*/

#include "libtvm/transition.hpp"

#include "libtvm/symbol.hpp"
#include "libtvm/tape.hpp"
#include "libtvm/transition_matchable.hpp"

#include <functional>
#include <tuple>
#include <vector>

template<class T> using ref = std::reference_wrapper<T>;
using std::tuple;
using std::vector;

using tvm::symbol;
using tvm::tape;
using tvm::tape_transition;
using tvm::transition;
using tvm::transition_matchable;

transition::transition(const vector<ref<const transition_matchable>>& read,
    const vector<ref<const transition_matchable>>& totape,
    const vector<tape_transition>& move) {
    // TODO: Vector length checks

    for (ref<const transition_matchable> r: read) {
        expect.push_back(r);
    }
    for (ref<const transition_matchable> w: totape) {
        write.push_back(w);
    }
    for (tape_transition t: move) {
        transitions.push_back(t);
    }
}

bool transition::match_and_run(vector<tape> tapes) const {
    // TODO: Vector length checks

    for (auto [t, m] = tuple {tapes.begin(), expect.begin()}; t != tapes.end(); ++t, ++m) {
        if (!(t->read().match(*m))) {
            return false;
        }
    }

    // All matched, now write and move
    for (auto [t, w, m] = tuple {tapes.begin(), write.begin(), transitions.begin()}; t != tapes.end(); ++t, ++w, ++m) {
        if (!(t->read().match(*w))) {
            t->write(symbol(*w));
        }
        t->move(*m);
    }

    return true;
}