#pragma once

#include "src/Puzzles/Puzzle.hpp"

class EightPuzzle : public Puzzle {
    public:
        EightPuzzle(const std::vector<int>& initialState) : Puzzle(initialState) {}

        int getGridSize() const override {
            return 3;
        }
        
        std::vector<int> getGoalState() const override {
            return {0, 1, 2, 3, 4, 5, 6, 7, 8};
        }
};
