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

Puzzle::Puzzle(std::string startingState, unsigned int size) 
    : currentState(std::move(startingState)), puzzleSize(size), solutionLength(0), lastAction(UNSET) {
    if (goalState.empty()) { 
        for (unsigned int i = 0; i < puzzleSize; i++) {
            goalState.push_back(i + '0'); 
        }
        gridSize = std::sqrt(puzzleSize);
    }
}

Puzzle::Puzzle(std::string startingState, unsigned int size, int length, int action)
    : currentState(std::move(startingState)),puzzleSize(size), solutionLength(length),lastAction(action){}

Puzzle::Puzzle(const char startingState[], unsigned int size)
    : currentState(startingState), puzzleSize(size), solutionLength(0), lastAction(UNSET) {
    if (goalState.empty()) {
        for (unsigned int i = 0; i < puzzleSize; i++) {
            goalState.push_back(i + '0');
        }
        gridSize = std::sqrt(puzzleSize);
    }
}

Puzzle::Puzzle(const char startingState[], unsigned int size, int length, int action)
    : currentState(std::move(startingState)),puzzleSize(size), solutionLength(length),lastAction(action){}

int Puzzle::findBlank() const {
    for (unsigned int i = 0; i < puzzleSize; ++i) {
        if (currentState[i] == '0') {
            return i;
        }
    }
    throw std::runtime_error("Blank space not found in the Puzzle.");
}

void Puzzle::moveBlankDown() {
    unsigned int blankIndex = findBlank();
    if (blankIndex < (gridSize * gridSize - gridSize)) {
        std::swap(currentState[blankIndex], currentState[blankIndex + 3]);
        lastAction = DOWN;
        ++solutionLength;
    }
}

void Puzzle::moveBlankUp() {
    unsigned int blankIndex = findBlank();
    if (blankIndex > (gridSize - 1)) {
        std::swap(currentState[blankIndex], currentState[blankIndex - 3]);
        lastAction = UP;
        ++solutionLength;
    }
}

void Puzzle::moveBlankRight() {
    unsigned int blankIndex = findBlank();
    if (blankIndex % gridSize != (gridSize-1)) {
        std::swap(currentState[blankIndex], currentState[blankIndex + 1]);
        lastAction = RIGHT;
        ++solutionLength;
    }
}

void Puzzle::moveBlankLeft() {
    unsigned int blankIndex = findBlank();
    if (blankIndex % gridSize != 0) {
        std::swap(currentState[blankIndex], currentState[blankIndex - 1]);
        lastAction = LEFT;
        ++solutionLength;
    }
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    if (lastAction != DOWN) {
        Puzzle up(*this);
        up.moveBlankUp();
        neighbors.push_back(std::move(up));
    }
    if (lastAction != RIGHT) {
        Puzzle left(*this);
        left.moveBlankLeft();
        neighbors.push_back(std::move(left));
    }
    if (lastAction != LEFT) {
        Puzzle right(*this);
        right.moveBlankRight();
        neighbors.push_back(std::move(right));
    }
    if (lastAction != UP) {
        Puzzle down(*this);
        down.moveBlankDown();
        neighbors.push_back(std::move(down));
    }
    return neighbors;
}

bool Puzzle::isGoal() const {
    return (goalState == currentState);
}


int Puzzle::getManhattanDistance() const {
    int totalDistance = 0;

    for (unsigned int i = 0; i < puzzleSize; i++) {
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