#pragma once

#include <vector>

class BFS {
    public:
        BFS(std::vector<int> state) : startState(state) {}
        void Resolve();

        std::vector<int> startState;
    private:
        std::vector<int> getGoal() { return {0, 1, 2, 3, 4, 5, 6, 7, 8}; };
};