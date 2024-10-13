#pragma once

#include "src/Puzzles/Puzzle.hpp"
#include "src/Puzzles/EightPuzzle.hpp"

#include <vector>

class BFS {
    public:
        BFS(std::vector<int> state) 
        : startState(state),
        puzzle(EightPuzzle(startState)) { }
        
        BFS(const Puzzle& puzzle) 
        : startState(puzzle.getStartState()),
        puzzle(puzzle) {}
        
        void Resolve();

        std::vector<int> startState;
    private:
        const Puzzle& puzzle;
        std::vector<int> getGoal() { return puzzle.getGoalState(); }
};