/*
    States are the nodes that compose a Turing Machine. They can represent either the status of the algorithm,
    or a certain step of a given process, among other things.

    In the context of a Turing Machine, each state has a set of transitions available, which may be equal or different
    than the transitions available in other states.
*/

#include "libtvm/state.hpp"

#include <string>

using std::string;
using tvm::state;

state::state(const string name): tag(name) {}

const string& state::name() {
    return tag;
}
