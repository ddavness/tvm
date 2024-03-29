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
        ~transition_matchable() = default;
        transition_matchable(const transition_matchable&) = default;
        transition_matchable& operator=(const transition_matchable&) = default;
        transition_matchable(transition_matchable&&) = default;
        transition_matchable& operator=(transition_matchable&&) = default;

      public:
        [[nodiscard]] virtual bool omatch(const tvm::transition_matchable&) const = 0;
        [[nodiscard]] virtual bool match(const tvm::transition_matchable&) const = 0;
        [[nodiscard]] int32_t index() const;
    };
} // namespace tvm
