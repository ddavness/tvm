/*
    A machine builder implements the Builder pattern for Turing Machines.

    It is useful because you can compose the machine as you're parsing the file.
*/

#pragma once

#include "libtvm/machine.hpp"
#include "libtvm/state.hpp"
#include "libtvm/transition.hpp"

#include <string>

namespace tvm::builder {
    class machine_builder {
      private:
        tvm::machine mach;

      public:
        machine_builder(std::string);

        const tvm::state& start_state();
        const tvm::state& accept_state();
        const tvm::state& reject_state();

        tvm::builder::machine_builder& add_state(tvm::state);
        tvm::builder::machine_builder& add_transition(const tvm::state&, tvm::transition, const tvm::state&);

        [[nodiscard]] const tvm::machine& finalize();
    };
} // namespace tvm::builder
