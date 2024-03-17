/*
    Because we want to support multiple copies of the same machine running at a given
    time, the machine class is actually just a blueprint. This class allows for multiple
    copies of the same machine to run independently of each other.
*/

#include "libtvm/machine.hpp"
#include "libtvm/state.hpp"

#include <utility>
#include <vector>

using std::get;
using std::vector;

using tvm::machine;
using tvm::machine_instance;
using tvm::state;
using tvm::tape;

machine_instance::machine_instance(tvm::machine& m, vector<tape> t):
    memory(std::move(t)),
    target(m),
    current(m.start()) {}

const machine& machine_instance::machine() const {
    return target;
}

const state& machine_instance::state() const {
    return current;
}

const vector<tape>& machine_instance::tapes() const {
    return memory;
}

bool machine_instance::step() {
    if (target.is_end(current)) {
        return false;
    }

    auto paths = target.user_states.at(current);
    for (auto path: paths) {
        if (get<0>(path).match_and_run(memory)) {
            current = get<1>(path);
            return true;
        }
    }

    // No appropriate transition was found; abort execution
    current = target.abort;
    return false;
}

bool machine_instance::run() {
    if (target.is_end(current)) {
        // TODO: Throw here because execution is over
        return false;
    }

    while (step()) {
        ;
    }

    return true;
}