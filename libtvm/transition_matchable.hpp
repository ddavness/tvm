/*
    The transition-matchable is an interfaces for symbol and symbol-like classes.
    Generally you will want to use the symbol class instead.
*/

#pragma once

#include <cstdint>

namespace tvm {
    class transition_matchable {
      private:
        int32_t idx;

      protected:
        transition_matchable(int32_t);
        [[nodiscard]] int32_t index() const;

      public:
        [[nodiscard]] virtual bool match(const tvm::transition_matchable&) const = 0;
    };
} // namespace tvm
