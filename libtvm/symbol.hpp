/*
    Defines a symbol. The symbol is the basic unit of information in computer theory.
*/

#pragma once

#include "libtvm/transition_matchable.hpp"

#include <unicode/uchar.h>
#include <map>
#include <ostream>

namespace tvm {
    class symbol final: public tvm::transition_matchable {
      private:
        [[nodiscard]] bool omatch(const tvm::transition_matchable&) const override;

      public:
        /**
         * Creates a new blank symbol.
         */
        symbol();

        /**
         * Creates a symbol using the given character (UTF-16 or UTF-32)
         */
        symbol(UChar);
        symbol(UChar32);

        /**
         * Upgrades an already existing transition_matchable into a symbol
         */
        symbol(const tvm::transition_matchable&);

        /**
         * Whether two symbols are equal
         */
        bool operator==(const tvm::symbol&) const;
        bool operator!=(const tvm::symbol&) const;

        /**
         * Attempt to match with another transition-matchable.
         */
        [[nodiscard]] bool match(const tvm::transition_matchable&) const override;
        [[nodiscard]] bool match(const tvm::symbol&) const;

        /**
         * Whether the symbol is blank
         */
        bool operator!() const;

        /**
         * Outputs the symbol into the given stream (e.g. cout)
         */
        friend std::ostream& operator<<(std::ostream&, const tvm::symbol&);
    };

    std::ostream& operator<<(std::ostream&, const tvm::symbol&);
} // namespace tvm
