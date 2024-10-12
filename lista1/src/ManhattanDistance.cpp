#include <iostream>
#include <cmath>

#include "ManhattanDistance.hpp"

int ManhattanDistance::Calculate(const std::vector<int>& state) const {
    // https://www.datacamp.com/pt/tutorial/manhattan-distance
    // dist man = |x1 - x2| + |y1 + y2|
    // calcular a soma das distancias para cada peça?
    // do estado atual até o goal.

    std::vector<int> goal = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    int totalDistance = 0;

    size_t stateSize = state.size();
    for (size_t i = 0; i < stateSize; i++) {
        int value = state[i];

        int currentRow = i / 3;
        int currentCol = i % 3;

        int goalRow = value / 3;
        int goalCol = value % 3;

        int distance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);

        totalDistance += distance;
    }

    return totalDistance;
}

