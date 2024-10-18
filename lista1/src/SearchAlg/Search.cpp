#include "src/SearchAlg/Search.hpp"
#include "src/Puzzle.hpp"

#include <string>
#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <queue>

PriorityPuzzle::PriorityPuzzle(Puzzle state, int insertionOrder)
: state(state),
insertionOrder(insertionOrder) {}

bool PriorityPuzzle::operator<(const PriorityPuzzle& other) const {
    return this->insertionOrder < other.insertionOrder;
}

bool GBFSPriorityComparator::operator()(const PriorityPuzzle& t, const PriorityPuzzle& other) const {
    if (t.state.h != other.state.h) return t.state.h > other.state.h;
    if (t.state.g != other.state.g) return t.state.g < other.state.g;
    return t.insertionOrder < other.insertionOrder;
}

bool AStarPriorityComparator::operator()(const PriorityPuzzle& t, const PriorityPuzzle& other) const {
    if (t.state.h + t.state.g != other.state.h + other.state.g) 
        return t.state.h + t.state.g > other.state.h + other.state.g;
    if (t.state.g != other.state.g) 
        return t.state.g < other.state.g;
    return t.insertionOrder < other.insertionOrder;
}

void Search::BFS(std::vector<int> startState) {
    int expandedNodes = 0;
    std::deque<Puzzle> open;
    std::unordered_set<std::string> closed;

    // MUDAR?
    std::string initialState;
    for (int value : startState) {
        initialState += (value == 0) ? '0' : '0' + value;
    }

    open.push_back(Puzzle(startState));
    closed.insert(initialState);

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        Puzzle current = open.front();
        open.pop_front();
        expandedNodes++;
        

        for (const Puzzle& neighbor : current.getNeighbors()) {
            if (neighbor.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                printf("%d, ", expandedNodes);
                printf("%d, ", neighbor.g);
                printf("%.6f, ", elapsedTime.count());
                printf("%.0f, ", 0.0f);
                printf("%d\n", Puzzle(startState).ManhattanDistance(startState));
                return;
            }

            // MUDAR?'
            std::string neighborState;
            for (int value : neighbor.state) {
                neighborState += (value == 0) ? '0' : '0' + value;
            }

            if (closed.find(neighborState) == closed.end()) {
                closed.insert(neighborState);
                open.push_back(neighbor);
            }
        }
    }

    printf("Unsolvable\n");
    return;
}

void Search::GBFS(std::vector<int> startState) {
    int nodesExpanded = 0;
    int insertOrder = 1;

    Puzzle initialPuzzle(startState);
    PriorityPuzzle initialStatePP(initialPuzzle, insertOrder);

    std::priority_queue<PriorityPuzzle, std::vector<PriorityPuzzle>, GBFSPriorityComparator> open;
    std::unordered_set<std::string> closed;

    open.push(std::move(initialStatePP));

    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (!open.empty()) {
        PriorityPuzzle n = open.top();
        open.pop();

        std::string newState;
        for (int value : n.state.state) {
            newState += (value == 0) ? '0' : '0' + value;
        }

        if (closed.find(newState) == closed.end()) {
            nodesExpanded++;
            closed.insert(newState);
            
            if (n.state.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                printf("%d, ", nodesExpanded - 1);
                printf("%d, ", n.state.g);
                printf("%.6f, ", elapsedTime.count());
                printf("%d\n", Puzzle(startState).ManhattanDistance(startState));
                return;
            }

            for (Puzzle& neighbor : n.state.getNeighbors()) {
                std::string newState2;
                for (int value : neighbor.state) {
                    newState2 += (value == 0) ? '0' : '0' + value;
                }

                if (closed.find(newState2) == closed.end()) {
                    insertOrder++;
                    PriorityPuzzle pp(neighbor, insertOrder);
                    open.push(std::move(pp));
                }
            }
        }
    }
    printf("Unsolvable\n");
    return;
}

void Search::AStar(std::vector<int> startState){
    int expandedNodes = 0;
    int insertOrder = 1;

    Puzzle initialPuzzle(startState);
    PriorityPuzzle initialStatePP(initialPuzzle, insertOrder);

    std::priority_queue<PriorityPuzzle,std::vector<PriorityPuzzle>, AStarPriorityComparator> open;
    std::unordered_set<std::string> closed;

    open.push(std::move(initialStatePP));

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        PriorityPuzzle current = open.top();
        open.pop();
        

        // MUDAR?'
        std::string neighborState;
        for (int value : current.state.state) {
            neighborState += (value == 0) ? '0' : '0' + value;
        }
        if (closed.find(neighborState) == closed.end()) {
            expandedNodes++;
            closed.insert(neighborState);
            if (current.state.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                std::cout << expandedNodes - 1 << ", ";
                std::cout << current.state.g << ", ";
                std::cout << elapsedTime.count() << ", ";
                std::cout << 0.0f << ", ";
                std::cout << Puzzle(startState).ManhattanDistance(startState) << "\n";
                return;
            }
            for (const Puzzle& neighbor : current.state.getNeighbors()) {
                std::string newState2;
                for (int value : neighbor.state) {
                    newState2 += (value == 0) ? '0' : '0' + value;
                }

                if (closed.find(newState2) == closed.end()) {
                    insertOrder++;
                    PriorityPuzzle pp(neighbor, insertOrder);
                    open.push(std::move(pp));
                }
            }
        }
    }
    std::cout << expandedNodes ;
    std::cout << " Unsolvable\n";
    
    return ;
}

