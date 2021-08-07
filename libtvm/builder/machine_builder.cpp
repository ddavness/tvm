#include "libtvm/builder/machine_builder.hpp"

#include "libtvm/machine.hpp"
#include "libtvm/transition.hpp"

#include <string>
#include <tuple>
#include <vector>

using std::string;
using std::tuple;
using std::vector;

using tvm::machine;
using tvm::state;
using tvm::transition;
using tvm::builder::machine_builder;

machine_builder::machine_builder(string t): mach(machine(t)) {}

machine_builder& machine_builder::add_state(state s) {
    if (mach.user_states.find(s) != mach.user_states.end()) {
        mach.user_states.at(s) = vector<tuple<transition, state&>>();
    } else {
        ; // TODO: Throw
    }

    return *this;
}

machine_builder& machine_builder::add_transition(tvm::state& from, tvm::transition t, tvm::state& to) {
    if (mach.user_states.find(from) != mach.user_states.end() && mach.user_states.find(to) != mach.user_states.end()) {
        mach.user_states.at(from).emplace_back(t, to);
    } else {
        ; // TODO: Throw
    }

    return *this;
}
