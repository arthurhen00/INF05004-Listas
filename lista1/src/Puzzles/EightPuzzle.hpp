#pragma once

#include "src/Puzzles/Puzzle.hpp"

class EightPuzzle : public Puzzle {
    public:
        EightPuzzle(const std::vector<int>& initialState, 
                    const std::vector<int>& goalState = {0 , 1, 2, 3, 4, 5, 6, 7, 8}) 
        : Puzzle(initialState, goalState) {}

        int getGridSize() const override {
            return 3;
        }
};
