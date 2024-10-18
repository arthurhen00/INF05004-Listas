#include "src/Puzzle.hpp"

#include <vector>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <cmath>

const std::vector<int> Puzzle::goalState = {0, 1, 2, 3, 4, 5, 6, 7, 8};

Puzzle::Puzzle(std::vector<int> startState) 
: state(startState),
g(0),
lastAction(UNSET) {
    h = this->ManhattanDistance(this->state);
}

Puzzle::Puzzle(std::vector<int> state, int g, int lastAction) 
: state(state),
g(g),
lastAction(lastAction) {
    h = this->ManhattanDistance(this->state);
}

int Puzzle::findBlank() const {
    size_t stateSize = state.size();
    for (size_t i = 0; i < stateSize; i++) {
        if (state[i] == 0) {
            return i;
        }
    }
    throw std::runtime_error("Blank space not found in the Puzzle.");
}

void Puzzle::moveBlankDown() {
    int blankIndex = findBlank();
    if (blankIndex < (gridSize * gridSize - gridSize)) {
        std::swap(state[blankIndex], state[blankIndex + gridSize]);
        lastAction = Action::DOWN;
        g++;
    }
}

void Puzzle::moveBlankUp() {
    int blankIndex = findBlank();
    if (blankIndex >= gridSize) {
        std::swap(state[blankIndex], state[blankIndex - gridSize]);
        lastAction = Action::UP;
        g++;
    }
}

void Puzzle::moveBlankRight() {
    int blankIndex = findBlank();
    if (blankIndex % gridSize != gridSize - 1) {
        std::swap(state[blankIndex], state[blankIndex + 1]);
        lastAction = Action::RIGHT;
        g++;
    }
}

void Puzzle::moveBlankLeft() {
    int blankIndex = findBlank();
    if (blankIndex % gridSize != 0) {
        std::swap(state[blankIndex], state[blankIndex - 1]);
        lastAction = Action::LEFT;
        g++;
    }
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    if (lastAction != DOWN) {
        Puzzle up(state, g, Action::UP);
        up.moveBlankUp();
        up.h = up.ManhattanDistance(up.state);
        neighbors.push_back(up);
    }
    if (lastAction != RIGHT) {
        Puzzle left(state, g, Action::LEFT);
        left.moveBlankLeft();
        left.h = left.ManhattanDistance(left.state);
        neighbors.push_back(left);
    }
    if (lastAction != LEFT) {
        Puzzle right(state, g, Action::RIGHT);
        right.moveBlankRight();
        right.h = right.ManhattanDistance(right.state);
        neighbors.push_back(right);
    }
    if (lastAction != UP) {
        Puzzle down(state, g, Action::DOWN);
        down.moveBlankDown();
        down.h = down.ManhattanDistance(down.state);
        neighbors.push_back(down);
    }
    return neighbors;
}

bool Puzzle::isGoal() const {
    return (state == goalState);
}

void Puzzle::printPuzzle() {
    for (int i = 0; i < 9; i++) {
        printf("%d ", state[i]);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
}

int Puzzle::ManhattanDistance(std::vector<int> state) {
    size_t stateSize = state.size();
    int totalDistance = 0;

    for (size_t i = 0; i < stateSize; i++) {
        int value = state[i];

        if (value == 0) {
            continue;
        }

        int currentRow = i / 3;
        int currentCol = i % 3;

        int goalRow = value / 3;
        int goalCol = value % 3;

        int distance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);

        totalDistance += distance;
    }

    return totalDistance;
}
