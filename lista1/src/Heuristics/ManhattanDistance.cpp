#include <iostream>
#include <cmath>

#include "src/Heuristics/ManhattanDistance.hpp"

int ManhattanDistance::Calculate() const {
    const std::vector<int>& state = puzzle.getState();
    const std::vector<int> goal = puzzle.getGoalState();
    int gridSize = puzzle.getGridSize();
    size_t stateSize = state.size();

    int totalDistance = 0;

    for (size_t i = 0; i < stateSize; i++) {
        int value = state[i];

        if (value == 0) {
            continue;
        }

        int currentRow = i / gridSize;
        int currentCol = i % gridSize;

        int goalRow = value / gridSize;
        int goalCol = value % gridSize;

        int distance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);

        totalDistance += distance;
    }

    return totalDistance;
}

