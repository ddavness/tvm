/*
    The machine class is a collection of states and transitions linking the states.

    In this context, because there are essentially infinite possibilities for machines, or,
    in other words, it is a very complex class, the job of creating Turing Machines is
    delegated to the machine_builder class instead.

    (If you're a OOP aficionado, yes, that's the Builder pattern).

    This class acts as a blueprint and doesn't actually contain execution information. For that,
    see the machine_instance class.
*/

#include "libtvm/machine.hpp"

#include "libtvm/state.hpp"
#include "libtvm/tape.hpp"
#include "libtvm/transition.hpp"

#include <forward_list>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using std::forward_list;
using std::string;
using std::tuple;
using std::vector;

using tvm::machine;
using tvm::machine_instance;
using tvm::state;
using tvm::tape;
using tvm::transition;

machine::machine(const string name): tag(name) {
    user_states.insert({initial, forward_list<tuple<transition, const state&>>()});
}

const string& machine::name() const {
    return tag;
}
bool machine::is_end(const tvm::state& state) const {
    return state == end_accept || state == end_reject || state == abort;
}
const state& machine::start() const {
    return initial;
}

machine_instance machine::fork() {
    size_t n = tape_number;
    vector<tape> tapes;
    for (size_t i = 0; i < n; ++i) {
        tape t;
        tapes.push_back(t);
    }

    return {*this, tapes};
}

machine_instance machine::fork(vector<tape> tapes) {
    if (tapes.size() != tape_number) {
        // TODO: Throw here due to tape count mismatch
    }
    return {*this, tapes};
}
