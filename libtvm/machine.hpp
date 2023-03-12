/*
    Defines a turing machine. A turing machine is a mathematical model able to run code.
    Computers (including smartphones, etc.) can emulate turing machines (to some degree, they don't have infinite
    memory).
*/

#pragma once

#include "libtvm/state.hpp"
#include "libtvm/transition.hpp"

#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <string>
#include <tuple>
#include <unordered_map>

namespace tvm::builder {
    class machine_builder;
} // namespace tvm::builder

namespace tvm {
    class machine_instance;

    class machine {
      private:
        machine(std::string);

        std::string tag;

        size_t tape_number = 0;

        const tvm::state end_accept = tvm::state("__tvm__ACCEPT__");
        const tvm::state end_reject = tvm::state("__tvm__REJECT__");
        const tvm::state abort = tvm::state("__tvm__ABORT__");
        const tvm::state initial = tvm::state("__tvm__START__");

        std::unordered_map<tvm::state, std::forward_list<std::tuple<tvm::transition, const tvm::state&>>> user_states;

        friend class tvm::builder::machine_builder;
        friend class tvm::machine_instance;

      public:
        const std::string& name() const;

        bool is_end(const tvm::state&) const;
        const tvm::state& start() const;

        tvm::machine_instance fork();
        tvm::machine_instance fork(std::vector<tvm::tape>);
    };

    class machine_instance {
      private:
        machine_instance(tvm::machine&, std::vector<tvm::tape>);

        std::vector<tvm::tape> memory;
        tvm::machine& target;
        tvm::state current;

        friend class tvm::machine;

      public:
        [[nodiscard]] const tvm::machine& machine() const;
        [[nodiscard]] const tvm::state& state() const;
        [[nodiscard]] const std::vector<tvm::tape>& tapes() const;

        bool step();
        bool run();
    };
} // namespace tvm
