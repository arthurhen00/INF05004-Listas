#include <iostream>
#include <vector>
#include "ManhattanDistance.hpp"

bool IsGoal(const std::vector<int>& state) {
    const std::vector<int> goalState = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    return state == goalState;
}

int main() {
    printf("Hello, World!\n");

    return EXIT_SUCCESS;
}

