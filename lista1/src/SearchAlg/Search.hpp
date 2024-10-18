#pragma once

#include "src/Puzzle.hpp"

#include <vector>

class Search {
    public:
        void BFS(std::vector<int> startState);
        void GBFS(std::vector<int> startState);
        void AStar(std::vector<int> startState);
    private:

};

struct PriorityPuzzle {
    Puzzle state;
    int insertionOrder;

    PriorityPuzzle(Puzzle state, int insertionOrder);
    bool operator<(const PriorityPuzzle &other) const;
};

struct GBFSPriorityComparator {
    bool operator()(const PriorityPuzzle& t, const PriorityPuzzle& other) const;
};
struct AStarPriorityComparator {
    bool operator()(const PriorityPuzzle& t, const PriorityPuzzle& other) const;
};