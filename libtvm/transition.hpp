/*
    Defines a transition. Transitions connect the states of a machine.
*/

#pragma once

#include "libtvm/tape.hpp"
#include "libtvm/transition_matchable.hpp"

#include <functional>
#include <vector>

namespace tvm {
    class transition {
      private:
        std::vector<std::reference_wrapper<const tvm::transition_matchable>> expect;
        std::vector<std::reference_wrapper<const tvm::transition_matchable>> write;
        std::vector<tvm::tape_transition> transitions;

      public:
        transition(const std::vector<std::reference_wrapper<const tvm::transition_matchable>>&,
            const std::vector<std::reference_wrapper<const tvm::transition_matchable>>&,
            const std::vector<tvm::tape_transition>&);

        [[nodiscard]] bool match_and_run(std::vector<tvm::tape>) const;
    };
} // namespace tvm
