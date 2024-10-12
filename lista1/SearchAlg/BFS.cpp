#include "Puzzles/Puzzle.hpp"
#include "Heuristics/Heuristic.hpp"
#include "SearchAlg/BFS.hpp"

#include <deque>
#include <unordered_set>


void BFS::Resolve() {
    const Puzzle& puzzle = heuristic.getPuzzle();
    const std::vector<int> startState = puzzle.getState();

    
}
        
