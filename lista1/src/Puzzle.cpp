#include "src/Puzzle.hpp"

#include <vector>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <cmath>

Puzzle::Puzzle(std::vector<char> state) 
: state(state), g(0), h(ManhattanDistance()), lastAction(UNSET){
    if(state.size() == 9){
        gridSize = 3;
    }else{
        gridSize = 4;
    }
}


int Puzzle::findBlank() const {
    size_t stateSize = state.size();
    for (size_t i = 0; i < stateSize; i++) {
        if (state[i] == '0') {
            return i;
        }
    }
    for (auto s: state){
        std::cout << s << ", ";
    }
    throw std::runtime_error("Blank space not found in the Puzzle.");
}

void Puzzle::moveBlankDown(const int blankIndex) {
    std::swap(state[blankIndex], state[blankIndex + gridSize]);
    lastAction = Action::DOWN;
    g++;
    h = ManhattanDistance();
}

void Puzzle::moveBlankUp(const int blankIndex) {
    std::swap(state[blankIndex], state[blankIndex - gridSize]);
    lastAction = Action::UP;
    g++;
    h = ManhattanDistance();
}

void Puzzle::moveBlankRight(const int blankIndex) {
    std::swap(state[blankIndex], state[blankIndex + 1]);
    lastAction = Action::RIGHT;
    g++;
    h = ManhattanDistance();
}

void Puzzle::moveBlankLeft(const int blankIndex) {
    std::swap(state[blankIndex], state[blankIndex - 1]);
    lastAction = Action::LEFT;
    g++;
    h = ManhattanDistance();
}

std::vector<Puzzle> Puzzle::getNeighbors() const {
    std::vector<Puzzle> neighbors;
    int blankIndex = findBlank();
    if (lastAction != DOWN && blankIndex >= gridSize) {
        Puzzle up(*this);
        up.moveBlankUp(blankIndex);
        if(up.state != state) neighbors.push_back(std::move(up));
    }
    if (lastAction != RIGHT && blankIndex % gridSize != 0) {
        Puzzle left(*this);
        left.moveBlankLeft(blankIndex);
        if(left.state != state) neighbors.push_back(std::move(left));
    }
    if (lastAction != LEFT && blankIndex % gridSize != gridSize - 1) {
        Puzzle right(*this);
        right.moveBlankRight(blankIndex);
        if(right.state != state) neighbors.push_back(std::move(right));
    }
    if (lastAction != UP && blankIndex < (gridSize * gridSize - gridSize)) {
        Puzzle down(*this);
        down.moveBlankDown(blankIndex);
        if(down.state != state) neighbors.push_back(std::move(down));
    }
    return neighbors;
}

bool Puzzle::isGoal() const {
    return h == 0;
}

void Puzzle::printPuzzle() {
    for (int i = 0; i < 9; i++) {
        printf("%d ", state[i]);
        if ((i + 1) % 3 == 0) {
            printf("\n");
        }
    }
}

int Puzzle::ManhattanDistance() {
    int totalDistance = 0;

    for (size_t i = 0; i < state.size(); i++) {
        int value = state[i] - '0';

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