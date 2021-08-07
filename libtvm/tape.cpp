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
        case tape_transition::LEFT:
            left();
            break;
        case tape_transition::RIGHT:
            right();
            break;
        case tape_transition::STAY:
            break;
    }
}

void tape::left() {
    // We are pointing to the rightmost symbol being represented, and that symbol is blank.
    // As such, we're removing it to save memory.
    if (needle + 1 == contents.size() && !contents.at(needle)) {
        contents.pop_back();
    }

    // Already at the leftmost of the deque, just add a blank symbol at the start of said deque
    if (needle-- == 0) {
        needle++; // cannot go below zero
        contents.emplace_front();
        return;
    }
}

void tape::right() {
    // We are pointing to the leftmost symbol being represented, and that symbol is blank.
    // As such, we're removing it to save memory.
    if (needle == 0 && !contents.at(needle)) {
        needle--; // one less element in the deque (needle being -1 will be addressed later)
        contents.pop_front();
    }

    // Already at the rightmost of the deque, just add a blank symbol at the end of said deque
    if (++needle == contents.size()) {
        contents.emplace_back();
    }
}
