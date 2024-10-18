#pragma once

#include "src/Puzzle.hpp"

#include <vector>
#include <string>
#include <unordered_set>


class Search {
    public:
        void BFS(std::vector<int>& startState);
        void GBFS(std::vector<int>& startState);
        void AStar(std::vector<int>& startState);
        void IDAStar(std::vector<int>& startState);
        void IDFS(std::vector<int>& startState);
    private:
        int IDAStarSearch(Puzzle& current, int bound, std::unordered_set<std::string>& closed, int &expandedNodes);
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