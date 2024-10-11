#include <iostream>
#include <vector>
#include "ManhattanDistance.hpp"

bool IsGoal(const std::vector<int>& state) {
    const std::vector<int> goalState = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    return state == goalState;
}

int main() {
    printf("Hello, World!\n");
    ManhattanDistance heuristic;

    printf("expected: 1 , res: [%d]\n", heuristic.Calculate({1, 0, 2, 3, 4, 5, 6, 7, 8}));
    printf("expected: 6 , res: [%d]\n", heuristic.Calculate({5, 1, 2, 0, 4, 3, 6, 7, 8}));
    printf("expected: 20, res: [%d]\n", heuristic.Calculate({8, 7, 6, 5, 4, 3, 2, 1, 0}));


    return EXIT_SUCCESS;
}

