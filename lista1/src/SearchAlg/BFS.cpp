#include "src/SearchAlg/BFS.hpp"
#include "src/Puzzle.hpp"
#include "src/Heuristics/ManhattanDistance.hpp"

#include <string>
#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>

int BFS(const Puzzle& puzzle) {
    int expandedNodes = 0;

    std::deque<Puzzle> open;
    std::unordered_set<std::string> closed;

    // MUDAR?
    std::string initialState;
    for (int value : puzzle.state) {
        initialState += (value == 0) ? '0' : '0' + value;
    }

    open.push_back(puzzle);
    closed.insert(initialState);

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        Puzzle current = open.front();
        open.pop_front();
        expandedNodes++;

        for (const Puzzle& neighbor : current.getNeighbors()) {
            if (neighbor.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                printf("%d, ", expandedNodes);
                printf("%d, ", neighbor.g);
                printf("%.6f, ", elapsedTime.count());
                printf("%.0f, ", 0.0f);
                printf("%d\n", ManhattanDistance(puzzle).Calculate());
                return neighbor.g;
            }

            // MUDAR?'
            std::string neighborState;
            for (int value : neighbor.state) {
                neighborState += (value == 0) ? '0' : '0' + value;
            }

            if (closed.find(neighborState) == closed.end()) {
                closed.insert(neighborState);
                open.push_back(neighbor);
            }
        }
    }

    printf("Unsolvable\n");
    return -1;
}
