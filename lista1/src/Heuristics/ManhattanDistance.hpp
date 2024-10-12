#pragma once

#include "src/Heuristics/Heuristic.hpp"

class ManhattanDistance : public Heuristic {
    public: 
        ManhattanDistance(const Puzzle& puzzle) : Heuristic(puzzle) {}
        int Calculate() const override;
};