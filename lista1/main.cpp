#include <iostream>
#include <vector>

#include "src/Heuristics/ManhattanDistance.hpp"
#include "src/Puzzles/EightPuzzle.hpp"
#include "src/SearchAlg/BFS.hpp"

int main() {
    printf("Hello, World!\n");

    printf("[%d]\n", BFS(ManhattanDistance(EightPuzzle({0, 1, 2, 3, 4, 5, 6, 7, 8}))).heuristic.Calculate());
    printf("[%d]\n", BFS(ManhattanDistance(EightPuzzle({1, 0, 2, 3, 4, 5, 6, 7, 8}))).heuristic.Calculate());
    printf("[%d]\n", BFS(ManhattanDistance(EightPuzzle({1, 2, 0, 3, 4, 5, 6, 7, 8}))).heuristic.Calculate());

    return EXIT_SUCCESS;
}
