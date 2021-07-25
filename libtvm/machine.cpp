/*
    The machine class is a collection of states and transitions linking the states.

    In this context, because there are essentially infinite possibilities for machines, or,
    in other words, it is a very complex class, the job of creating Turing Machines is
    delegated to the machine_builder class instead.

    (If you're a OOP aficionado, yes, that's the Builder pattern)
*/

#include "libtvm/machine.hpp"

#include "libtvm/state.hpp"
#include "libtvm/transition.hpp"

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using std::string;
using std::tuple;
using std::vector;

using tvm::machine;
using tvm::state;
using tvm::transition;

machine::machine(const string name): tag(name) {
    user_states.at(initial) = vector<tuple<transition, state&>>();
}

const string& machine::name() const {
    return tag;
}
bool machine::is_end(tvm::state& state) const {
    return state == end_accept || state == end_reject || state == abort;
}
const state& machine::start() const {
    return initial;
}
