#pragma once

#include "src/Puzzle.hpp"

#include <vector>
#include <string>
#include <unordered_set>


class Search {
    public:
        void BFS(Puzzle& puzzle);
        void GBFS(Puzzle& puzzle);
        void AStar(Puzzle& puzzle);
        void IDAStar(Puzzle& puzzle);
        void IDFS(Puzzle& puzzle);
    private:
        int IDAStarSearch(Puzzle& current, int bound, int &expandedNodes);
        int IDFSSearch(Puzzle& current, int depth, int& expandedNodes);

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