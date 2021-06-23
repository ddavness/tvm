/*
    A tape is a container of infinite size that holds symbols. This is akin to the memory of a computer.

    The original tape definition is limited to the left (i.e. unidirectional) and infinite to the right.
    After each transition, the needle (that points to the symbol being read/written) can be moved either left or right.

    Let's call this tape "LR unidirectional"

    The tape implementation in this library has two extensions:
    * It is infinite both to the left and to the right;
    * After each transition, the tape needle can also not move (stay);

    We can call it a "LSR bidirectional" tape.

    * THEOREM: Given a turing machine operating in a LSR bidirectional tape, we can build an equivalent
    turing machine operating in a LR unidirectional tape (i.e. that does exactly the same thing).
*/

#include "libtvm/tape.hpp"

#include <vector>

using std::vector;
using tvm::symbol;
using tvm::tape;
using tvm::tape_transition;

// Public constructors
tape::tape(): needle(0) {
    contents.emplace_back(symbol());
}
tape::tape(const vector<symbol>& symbols, uint64_t n): needle(n) {
    for (symbol s: symbols) {
        contents.emplace_back(s);
    }
}

const symbol& tape::read() const {
    return contents.at(needle);
}

void tape::write(const symbol& sym) {
    contents.at(needle) = sym;
}

void tape::move(tape_transition t) {
    switch (t) {
        case tape_transition::RIGHT:
            needle++;
            break;
        case tape_transition::LEFT:
            needle--;
            break;
        case tape_transition::STAY:
            break;
    }
}
