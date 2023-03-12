#include "libtvm/builder/machine_builder.hpp"

#include "libtvm/machine.hpp"
#include "libtvm/transition.hpp"

#include <cstddef>
#include <forward_list>
#include <string>
#include <tuple>
#include <vector>

using std::forward_list;
using std::get;
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
    if (mach.user_states.find(s) == mach.user_states.end()) {
        mach.user_states.emplace(s, forward_list<tuple<transition, const state&>>());
    } else {
        throw "State already exists!";
    }

    return *this;
}

machine_builder& machine_builder::add_transition(const state& from, transition t, const state& to) {
    if (mach.tape_number != 0 && t.size() != mach.tape_number) {
        throw "Inconsistent tape lengths";
    }

    if (mach.user_states.find(from) == mach.user_states.end()
        || (!mach.is_end(to) && mach.user_states.find(to) == mach.user_states.end())) {
        throw "State not found";
    }

    if (mach.is_end(from)) {
        throw "Transition starts from an end state";
    }

    auto& bucket = mach.user_states.at(from);
    size_t nw = t.num_wildcards();
    for (auto it = bucket.before_begin(); it != bucket.end();) {
        auto here = it;
        it++;
        if (it == bucket.end() || get<0>(*it).num_wildcards() > nw) {
            // We've reached the end
            bucket.emplace_after(here, t, to);
            break;
        }

        if (t.same_expect(get<0>(*(it)))) {
            throw "Non-deterministic code is not supported!";
        }
    }

    if (mach.tape_number == 0) {
        mach.tape_number = t.size();
    }

    return *this;
}

const machine& machine_builder::finalize() {
    if (mach.tape_number == 0) {
        throw "No transitions were added!";
    }
    return mach;
}
