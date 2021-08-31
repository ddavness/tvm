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

const state& machine_builder::start_state() {
    return mach.initial;
}
const state& machine_builder::accept_state() {
    return mach.end_accept;
}
const state& machine_builder::reject_state() {
    return mach.end_reject;
}

machine_builder& machine_builder::add_state(state s) {
    if (mach.user_states.find(s) != mach.user_states.end()) {
        mach.user_states.at(s) = vector<tuple<transition, const state&>>();
    } else {
        ; // TODO: Throw
    }

    return *this;
}

machine_builder& machine_builder::add_transition(const state& from, transition t, const state& to) {
    if (mach.user_states.find(from) != mach.user_states.end() && mach.user_states.find(to) != mach.user_states.end()) {
        mach.user_states.at(from).emplace_back(t, to);
    } else {
        ; // TODO: Throw
    }

    return *this;
}

const machine& machine_builder::finalize() {
    return mach;
}
