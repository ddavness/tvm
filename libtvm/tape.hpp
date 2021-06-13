/*
    Defines a tape. A tape is an infinite symbol container used in Turing Machines.

    Tapes in this library are bidirectional.
*/

#pragma once

#include "libtvm/symbol.hpp"

#include <deque>

namespace tvm {
    enum class tape_transition : int8_t { LEFT = -1, STAY = 0, RIGHT = 1 };

    class tape {
      private:
        std::deque<tvm::symbol> contents;
        uint64_t needle;

      public:
        /**
         * @returns An empty tape.
         */
        tape();

        /**
         * Builds a tape from the given symbol container.
         * The needle will be set at the position defined on the second parameter, if defined.
         * Otherwise it will be set at the start of the container.
         *
         * @returns A tape built from the given symbol set.
         */
        template<typename SequenceContainer> tape(const SequenceContainer&, uint64_t = 0);

        /**
         * Reads the symbol stored in the tape in the current position.
         *
         * @returns The symbol read.
         */
        [[nodiscard]] const tvm::symbol& read() const;

        /**
         * Writes the given symbol to the current position of the tape.
         */
        void write(const tvm::symbol&);

        /**
         * Moves the needle of the tape according to the transition specified.
         */
        void move(tvm::tape_transition);
    };
} // namespace tvm
