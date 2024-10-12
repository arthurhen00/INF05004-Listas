#pragma once

#include "src/Heuristics/Heuristic.hpp"

#include <vector>

class BFS {
    public:
        BFS(const Heuristic& heuristic) : heuristic(heuristic) {}
        void Resolve();

        const Heuristic& heuristic;
    private:
};