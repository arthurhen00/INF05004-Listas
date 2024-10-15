#include "src/SearchAlg/BFS.hpp"
#include "src/Puzzle.hpp"

#include <string>
#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>

int BFS(Puzzle initialState) {
    int expandedNodes = 0;


    std::deque<Puzzle> open;
    std::unordered_set<std::string> closed;

    open.push_back(initialState);
    closed.insert(initialState.currentState);

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        Puzzle current = open.front();
        open.pop_front();
        expandedNodes++;

        for (const Puzzle& neighbor : current.getNeighbors()) {
            
            /*
            std::cout << neighbor << "  ";
            std::cout << "open:" << std::endl;
            for(auto &a : open){
                std::cout<< "    " << a << std::endl;
            }
            */


            if (neighbor.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                printf("%d, ", expandedNodes);
                printf("%d, ", neighbor.solutionLength);
                printf("%.6f, ", elapsedTime.count());
                printf("%.0f, ", 0.0f);
                printf("%d\n", initialState.getManhattanDistance());
                return neighbor.solutionLength;
            }

            // s' not in closed
            if (closed.find(neighbor.currentState) == closed.end()) {
                closed.insert(neighbor.currentState);
                open.push_back(neighbor);
                //std::cout << "Pushed: " << neighbor << std::endl;
            }
        }
    }
    printf("%d, ", expandedNodes);
    printf("Unsolvable\n");
    return -1;
}
