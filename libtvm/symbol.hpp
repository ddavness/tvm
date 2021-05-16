/*
    Defines a symbol. The symbol is the basic unit of information in computer theory.
*/

#pragma once

#include "libtvm/version.hpp"

#include <unicode/uchar.h>
#include <map>
#include <ostream>

namespace tvm {
    class symbol {
      private:
        static const std::map<UChar32, int32_t> literals;
        const int32_t index;

      public:
        /**
         * Creates a new blank symbol.
         */
        symbol();

        /**
         * Creates a symbol using the given character (UTF-16 or UTF-32)
         */
        symbol(UChar l);
        symbol(UChar32 l);

        /**
         * Whether two symbols are equal
         */
        bool operator==(const tvm::symbol&) const;
        bool operator!=(const tvm::symbol&) const;

        /**
         * Whether the symbol is blank
         */
        bool operator!() const;

        /**
         * Outputs the symbol into the given stream (e.g. cout)
         */
        std::ostream& operator<<(std::ostream&) const;
    };
} // namespace tvm
