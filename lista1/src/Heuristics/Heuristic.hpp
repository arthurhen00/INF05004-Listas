#pragma once

#include "src/Puzzles/Puzzle.hpp"

class Heuristic {
    public:
        Heuristic(const Puzzle& puzzle) : puzzle(puzzle) {}
        virtual int Calculate() const = 0;
        virtual ~Heuristic() {}

        const Puzzle& getPuzzle() const { return puzzle; }

    protected:
        const Puzzle& puzzle;
};