#include <vector>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "Puzzle.hpp"


std::string Puzzle::goalState;

std::ostream& operator<<(std::ostream& os, const Puzzle& obj) {
    os << "(" << obj.currentState << ")";
    return os;
}

Puzzle::Puzzle(std::string startingState, unsigned int puzzleSize) 
    : currentState(std::move(startingState)), size(puzzleSize), solutionLength(0), lastAction(UNSET) {
    if (goalState.empty()) { 
        for (unsigned int i = 0; i < puzzleSize; i++) {
            goalState.push_back(i + '0'); 
        }
    }
}

Puzzle::Puzzle(std::string startingState, unsigned int puzzleSize, int length, int action)
    : currentState(std::move(startingState)),size(puzzleSize), solutionLength(length),lastAction(action){}

Puzzle::Puzzle(const char startingState[], unsigned int puzzleSize)
    : currentState(startingState), size(puzzleSize), solutionLength(0), lastAction(UNSET) {
    if (goalState.empty()) {
        for (unsigned int i = 0; i < puzzleSize; i++) {
            goalState.push_back(i + '0');
        }
    }
}

Puzzle::Puzzle(const char startingState[], unsigned int puzzleSize, int length, int action)
    : currentState(std::move(startingState)),size(puzzleSize), solutionLength(length),lastAction(action){}

int Puzzle::findBlank() const {
    for (unsigned int i = 0; i < size; ++i) {
        if (currentState[i] == '0') {
            return i;
        }
    }
    throw std::runtime_error("Blank space not found in the Puzzle.");
}

Puzzle Puzzle::moveDown() const {
    int blankIndex = findBlank();
    std::string newcurrentState = currentState;
    if(blankIndex <= 5){
        std::swap(newcurrentState[blankIndex], newcurrentState[blankIndex + 3]);
    }
    return Puzzle(newcurrentState, size, solutionLength + 1, DOWN);
}

Puzzle Puzzle::moveUp() const {
    int blankIndex = findBlank();
    std::string newcurrentState = currentState;
    if(blankIndex > 2){
        std::swap(newcurrentState[blankIndex], newcurrentState[blankIndex - 3]);
    }
    return Puzzle(newcurrentState, size, solutionLength + 1, UP);
}

Puzzle Puzzle::moveRight() const {
    int blankIndex = findBlank();
    std::string newcurrentState = currentState;
    if(blankIndex % 3 != 2){
        std::swap(newcurrentState[blankIndex], newcurrentState[blankIndex + 1]);
    }
    return Puzzle(newcurrentState, size, solutionLength + 1, RIGHT);
}

Puzzle Puzzle::moveLeft() const {
    int blankIndex = findBlank();
    std::string newcurrentState = currentState;
    if(blankIndex % 3 != 0){
        std::swap(newcurrentState[blankIndex], newcurrentState[blankIndex - 1]);
    }
    return Puzzle(newcurrentState, size, solutionLength + 1, LEFT);
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    if (lastAction != DOWN) neighbors.push_back(moveUp());
    if (lastAction != RIGHT) neighbors.push_back(moveLeft());
    if (lastAction != LEFT) neighbors.push_back(moveRight());
    if (lastAction != UP) neighbors.push_back(moveDown());
    return neighbors;
}

bool Puzzle::isGoal() const {
    return (goalState == currentState);
}


int Puzzle::getManhattanDistance() const {
    int gridSize = std::sqrt(size);

    int totalDistance = 0;

    for (unsigned int i = 0; i < size; i++) {
        int value = currentState[i];

        if (value == 0) {
            continue;
        }

        int currentRow = i / gridSize;
        int currentCol = i % gridSize;

        int goalRow = value / gridSize;
        int goalCol = value % gridSize;

        int distance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);

        totalDistance += distance;
    }

    return totalDistance;
}