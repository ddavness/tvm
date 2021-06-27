/*
    The symbol-wildcard is a transition-matchable that matches all transition-matchables.
*/

#pragma once

#include "libtvm/transition_matchable.hpp"

#include <ostream>

namespace tvm {
    class symbol_wildcard: public tvm::transition_matchable {
      public:
        /**
         * Creates a wildcard symbol. Will always match with a matchable.
         */
        symbol_wildcard();

        /**
         * Will always be equal to another wildcard.
         */
        bool operator==(const tvm::symbol_wildcard&) const;
        bool operator!=(const tvm::symbol_wildcard&) const;

        /**
         * Outputs the wildcard into the given stream (e.g. cout)
         */
        friend std::ostream& operator<<(std::ostream&, const tvm::symbol_wildcard&);

        /**
         * Attempt to match with another transition-matchable.
         */
        bool match(const tvm::transition_matchable&) const;
    };

    std::ostream& operator<<(std::ostream&, const tvm::symbol_wildcard&);
} // namespace tvm
