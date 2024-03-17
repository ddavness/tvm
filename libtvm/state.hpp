/*
    Defines a state. States are nodes that compose a Turing Machine.
*/

#pragma once

#include <cstddef>
#include <functional>
#include <string>

namespace tvm {
    class state {
      private:
        std::string tag;
        friend struct std::hash<tvm::state>;

      public:
        state(std::string);

        [[nodiscard]] const std::string& name() const;

        bool operator==(const tvm::state&) const;
    };
} // namespace tvm

template<> struct std::hash<tvm::state> {
    std::size_t operator()(const tvm::state&) const;
};
