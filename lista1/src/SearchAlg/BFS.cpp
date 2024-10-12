#include "src/Puzzles/Puzzle.hpp"
#include "src/Heuristics/Heuristic.hpp"
#include "src/SearchAlg/BFS.hpp"

#include <deque>
#include <unordered_set>


void BFS::Resolve() {
    const Puzzle& puzzle = heuristic.getPuzzle();
    const std::vector<int> startState = puzzle.getState();

    
}
        
