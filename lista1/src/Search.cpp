#include "src/Search.hpp"
#include "src/Puzzle.hpp"

#include <string>
#include <deque>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <limits>



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

void Search::BFS(Puzzle& puzzle) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    std::deque<Puzzle> open;
    std::unordered_set<unsigned long long> closed;


    open.push_back(puzzle);
    closed.insert(puzzle.state);


    while (!open.empty()) {
        Puzzle current = open.front();
        open.pop_front();
        expandedNodes++;

        for (const Puzzle& neighbor : current.getNeighbors()) {
            if (neighbor.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                fprintf(stderr, "%d,%d,%lf,%.0lf,%d\n"
                    , expandedNodes
                    , neighbor.g
                    , elapsedTime.count()
                    , 0.0f
                    , puzzle.ManhattanDistance()
                );
                return;
            }

            if (closed.find(neighbor.state) == closed.end()) {
                closed.insert(neighbor.state);
                open.push_back(neighbor);
            }
        }
    }

    fprintf(stderr, "-,-,-,-,-\n");
    return;
}

void Search::GBFS(Puzzle& puzzle) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int nodesExpanded = 0;
    int insertOrder = 1;

    heuristicAccum = 0;
    heuristicCounter = 0;

    PriorityPuzzle initialStatePP(puzzle, insertOrder);

    std::priority_queue<PriorityPuzzle, std::vector<PriorityPuzzle>, GBFSPriorityComparator> open;
    std::unordered_set<unsigned long long> closed;

    open.push(std::move(initialStatePP));

    
    while (!open.empty()) {
        PriorityPuzzle n = open.top();
        open.pop();

        if (closed.find(n.state.state) == closed.end()) {
            nodesExpanded++;
            closed.insert(n.state.state);
            
            if (n.state.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                fprintf(stderr, "%d,%d,%lf,%lf,%d\n"
                    , nodesExpanded - 1
                    , n.state.g
                    , elapsedTime.count()
                    , static_cast<double>(heuristicAccum) / heuristicCounter
                    , puzzle.ManhattanDistance()
                );
                return;
            }

            for (Puzzle& neighbor : n.state.getNeighbors()) {

                if (closed.find(neighbor.state) == closed.end()) {
                    insertOrder++;
                    PriorityPuzzle pp(neighbor, insertOrder);
                    open.push(std::move(pp));
                }
            }
        }
    }

    fprintf(stderr, "-,-,-,-,-\n");
    return;
}

void Search::AStar(Puzzle& puzzle){
    auto startTime = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int insertOrder = 1;
    heuristicAccum = 0;
    heuristicCounter = 0;
    PriorityPuzzle initialStatePP(puzzle, insertOrder);

    std::priority_queue<PriorityPuzzle,std::vector<PriorityPuzzle>, AStarPriorityComparator> open;
    std::unordered_set<unsigned long long> closed;

    open.push(std::move(initialStatePP));


    while (!open.empty()) {
        PriorityPuzzle current = open.top();
        open.pop();

        
        if (closed.find(current.state.state) == closed.end()) {
            expandedNodes++;
            
            closed.insert(current.state.state);
            if (current.state.isGoal()) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = endTime - startTime;

                fprintf(stderr, "%d,%d,%lf,%lf,%d\n"
                    , expandedNodes - 1
                    , current.state.g
                    , elapsedTime.count()
                    , static_cast<double>(heuristicAccum) / heuristicCounter
                    , puzzle.ManhattanDistance()
                );

                
                return;
            }

            for (const Puzzle& neighbor : current.state.getNeighbors()) {
                if (closed.find(neighbor.state) == closed.end()) {
                    insertOrder++;
                    PriorityPuzzle pp(neighbor, insertOrder);
                    open.push(std::move(pp));
                }
            }
        }
    }
    
    fprintf(stderr, "-,-,-,-,-\n");
    return ;
}

void Search::IDAStar(Puzzle& puzzle){
    auto startTime = std::chrono::high_resolution_clock::now();
    int expandedNodes = 0;
    int bound = puzzle.h;
    heuristicAccum = 0;
    heuristicCounter = 0;
    while (true)
    {   
        heuristicAccum += puzzle.h;
        heuristicCounter += 1;
        //std::cout << "ida" << std::endl;
        int result = IDAStarSearch(puzzle, bound, expandedNodes);
        
        if(result < 0){
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedTime = endTime - startTime;

            fprintf(stderr, "%d,%d,%lf,%lf,%d\n"
                , expandedNodes
                , -result
                , elapsedTime.count()
                , static_cast<double>(heuristicAccum) / heuristicCounter
                , puzzle.h
            );
            return;
        }
        
        bound = result;
    }
}

int Search::IDAStarSearch(Puzzle& current, int bound, int &expandedNodes){
    int f = current.g + current.h;
    if(f > bound){
        return f;
    }
    if(current.isGoal()) return -current.g;

    int nextLimit = std::numeric_limits<int>::max();
    expandedNodes++; 
    for(Puzzle& neighbor : current.getNeighbors()){
        int result = IDAStarSearch(neighbor,bound, expandedNodes);
        if(result < 0) return result;
        nextLimit = std::min(nextLimit,result);
    }
    return nextLimit;
}

void Search::IDFS(Puzzle& puzzle){
    auto startTime = std::chrono::high_resolution_clock::now();
    int depth = 1;
    int expandedNodes = 0;
    while (true)
    {
        int result = IDFSSearch(puzzle,depth - 1,expandedNodes);
        if(result > 0){
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedTime = endTime - startTime;

            fprintf(stderr, "%d,%d,%lf,%.0lf,%d\n"
                , expandedNodes
                , result
                , elapsedTime.count()
                , 0.0f
                , puzzle.h
            );
            return;
        }
        depth++;
    }
    
}

int Search::IDFSSearch(Puzzle& current, int depth, int& expandedNodes){
    if(current.isGoal()){
        return current.g;
    }
    if(depth > 0){
        expandedNodes++;
        for(Puzzle& neighbor : current.getNeighbors()){
            int result = IDFSSearch(neighbor,depth - 1, expandedNodes);
            if(result > 0){
                return result;
            }
        }
    }

    return 0;
}