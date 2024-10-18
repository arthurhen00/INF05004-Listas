#include "src/Puzzle.hpp"

#include <vector>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <cmath>

const std::vector<int> Puzzle::goalState = {0, 1, 2, 3, 4, 5, 6, 7, 8};

Puzzle::Puzzle(std::vector<int> startState) 
: state(startState), g(0), h(ManhattanDistance(startState)), lastAction(UNSET) {}

Puzzle::Puzzle(std::vector<int> state, int g, int lastAction) 
: state(state), g(g), lastAction(lastAction) {}

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
        h = ManhattanDistance(state);
    }
}

void Puzzle::moveBlankUp() {
    int blankIndex = findBlank();
    if (blankIndex >= gridSize) {
        std::swap(state[blankIndex], state[blankIndex - gridSize]);
        lastAction = Action::UP;
        g++;
        h = ManhattanDistance(state);
    }
}

void Puzzle::moveBlankRight() {
    int blankIndex = findBlank();
    if (blankIndex % gridSize != gridSize - 1) {
        std::swap(state[blankIndex], state[blankIndex + 1]);
        lastAction = Action::RIGHT;
        g++;
        h = ManhattanDistance(state);
    }
}

void Puzzle::moveBlankLeft() {
    int blankIndex = findBlank();
    if (blankIndex % gridSize != 0) {
        std::swap(state[blankIndex], state[blankIndex - 1]);
        lastAction = Action::LEFT;
        g++;
        h = ManhattanDistance(state);
    }
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    if (lastAction != DOWN) {
        Puzzle up(state, g, Action::UP);
        up.moveBlankUp();
        neighbors.push_back(std::move(up));
    }
    if (lastAction != RIGHT) {
        Puzzle left(state, g, Action::LEFT);
        left.moveBlankLeft();
        neighbors.push_back(std::move(left));
    }
    if (lastAction != LEFT) {
        Puzzle right(state, g, Action::RIGHT);
        right.moveBlankRight();
        neighbors.push_back(std::move(right));
    }
    if (lastAction != UP) {
        Puzzle down(state, g, Action::DOWN);
        down.moveBlankDown();
        neighbors.push_back(std::move(down));
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
