#include <iostream>
#include <vector>

#include "src/Heuristics/ManhattanDistance.hpp"
#include "src/Puzzles/EightPuzzle.hpp"
#include "src/SearchAlg/BFS.hpp"

int main() {
    printf("Hello, World!\n");

    printf("[%d]\n", ManhattanDistance(EightPuzzle({0, 1, 2, 3, 4, 5, 6, 7, 8})).Calculate());
    printf("[%d]\n", ManhattanDistance(EightPuzzle({1, 0, 2, 3, 4, 5, 6, 7, 8})).Calculate());
    printf("[%d]\n", ManhattanDistance(EightPuzzle({1, 2, 0, 3, 4, 5, 6, 7, 8})).Calculate());

    BFS({0, 6, 1, 7, 4, 2, 3, 8, 5}).Resolve();
    BFS({5, 0, 2, 6, 4, 8, 1, 7, 3}).Resolve();
    BFS({2, 4, 7, 0, 3, 6, 8, 1, 5}).Resolve();

    return EXIT_SUCCESS;
}
