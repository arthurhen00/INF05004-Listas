#include "src/SearchAlg/BFS.hpp"
#include "State.cpp"
#include "src/Heuristics/ManhattanDistance.hpp"
#include "src/Puzzles/EightPuzzle.hpp"

#include <deque>
#include <unordered_set>
#include <chrono>

void BFS::Resolve() {
    int nodesExpanded = 0;
    
    if (startState == getGoal()) {
        printf("Start = goal\n");
        return;
    }

    char* data = new char[9];
    for (size_t i = 0; i < startState.size(); i++) {
        data[i] = (startState[i] == 0) ? ' ' : '0' + startState[i];
    }

    State initialState(data, 0, ManhattanDistance(EightPuzzle(startState)).Calculate());
    delete[] data;

    std::deque<State> open;
    std::unordered_set<std::string> closed;

    open.push_back(initialState);
    closed.insert(std::string(initialState.data, 9));

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        State current = open.front();
        open.pop_front();

        nodesExpanded++;

        for (const State& neighbor : current.getNeighbors()) {
            if (neighbor.isGoal()) {
                int solutionLength = current.solutionLength + 1;
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                printf("%d, ", nodesExpanded);
                printf("%d, ", solutionLength);
                printf("%.6f, ", elapsedTime.count());
                printf("%.0f, ", 0.0f);
                printf("%d\n", initialState.heuristicValue);
                return;
            }

            // s' not in closed
            if (closed.find(std::string(neighbor.data, 9)) == closed.end()) {
                closed.insert(std::string(neighbor.data, 9));
                open.push_back(neighbor);
            }
        }
    }

    printf("Unsolvable\n");
}
