/*
    Defines a turing machine. A turing machine is a mathematical model able to run code.
    Computers (including smartphones, etc.) can emulate turing machines (to some degree, they don't have infinite
    memory).
*/

#pragma once

#include "libtvm/state.hpp"
#include "libtvm/transition.hpp"

#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace tvm::builder {
    class machine_builder;
} // namespace tvm::builder

namespace tvm {
    class machine {
      private:
        machine(std::string);

        std::string tag;

        const tvm::state end_accept = tvm::state("ACCEPT");
        const tvm::state end_reject = tvm::state("REJECT");
        const tvm::state abort = tvm::state("ABORT");
        const tvm::state initial = tvm::state("START");

        std::unordered_map<tvm::state, std::vector<std::tuple<tvm::transition, const tvm::state&>>> user_states;

        friend class tvm::builder::machine_builder;

      public:
        const std::string& name() const;

        bool is_end(tvm::state&) const;
        const tvm::state& start() const;
    };
} // namespace tvm
