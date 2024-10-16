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
lastAction(UNSET) { }

Puzzle::Puzzle(std::vector<int> state, int g, int lastAction) 
: state(state),
g(g),
lastAction(lastAction) { }

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
        neighbors.push_back(up);
    }
    if (lastAction != RIGHT) {
        Puzzle left(state, g, Action::LEFT);
        left.moveBlankLeft();
        neighbors.push_back(left);
    }
    if (lastAction != LEFT) {
        Puzzle right(state, g, Action::RIGHT);
        right.moveBlankRight();
        neighbors.push_back(right);
    }
    if (lastAction != UP) {
        Puzzle down(state, g, Action::DOWN);
        down.moveBlankDown();
        neighbors.push_back(down);
    }
    return neighbors;
}

bool Puzzle::isGoal() const {
    return (state == goalState);
}