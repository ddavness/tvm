/*
    Defines a state. States are nodes that compose a Turing Machine.
*/

#pragma once

#include <string>

namespace tvm {
    class state {
      private:
        const std::string tag;

      public:
        state(std::string);

        [[nodiscard]] const std::string& name();
    };
} // namespace tvm
