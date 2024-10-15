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

void Puzzle::moveDown() {
    int blankIndex = findBlank();
    if (blankIndex <= 5) {
        std::swap(currentState[blankIndex], currentState[blankIndex + 3]);
        lastAction = DOWN;
        ++solutionLength;
    }
}

void Puzzle::moveUp() {
    int blankIndex = findBlank();
    if (blankIndex > 2) {
        std::swap(currentState[blankIndex], currentState[blankIndex - 3]);
        lastAction = UP;
        ++solutionLength;
    }
}

void Puzzle::moveRight() {
    int blankIndex = findBlank();
    if (blankIndex % 3 != 2) {
        std::swap(currentState[blankIndex], currentState[blankIndex + 1]);
        lastAction = RIGHT;
        ++solutionLength;
    }
}

void Puzzle::moveLeft() {
    int blankIndex = findBlank();
    if (blankIndex % 3 != 0) {
        std::swap(currentState[blankIndex], currentState[blankIndex - 1]);
        lastAction = LEFT;
        ++solutionLength;
    }
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    if (lastAction != DOWN) {
        Puzzle up(*this);
        up.moveUp();
        neighbors.push_back(std::move(up));
    }
    if (lastAction != RIGHT) {
        Puzzle left(*this);
        left.moveLeft();
        neighbors.push_back(std::move(left));
    }
    if (lastAction != LEFT) {
        Puzzle right(*this);
        right.moveRight();
        neighbors.push_back(std::move(right));
    }
    if (lastAction != UP) {
        Puzzle down(*this);
        down.moveDown();
        neighbors.push_back(std::move(down));
    }
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