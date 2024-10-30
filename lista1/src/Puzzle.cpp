#include "src/Puzzle.hpp"

#include <vector>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <cmath>


size_t heuristicAccum = 0;
size_t heuristicCounter = 0;

Puzzle::Puzzle(std::vector<char> state) 
: state(state), g(0), lastAction(UNSET){
    if(state.size() == 9){
        gridSize = 3;
    }else{
        gridSize = 4;
    }

    h = ManhattanDistance();
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
    int tileIndex = blankIndex + gridSize;
    updateManhattanDistance(tileIndex, blankIndex);
    std::swap(state[blankIndex], state[tileIndex]);
    lastAction = Action::DOWN;
    g++;

}

void Puzzle::moveBlankUp(const int blankIndex) {
    int tileIndex = blankIndex - gridSize;
    updateManhattanDistance(tileIndex, blankIndex);
    std::swap(state[blankIndex], state[tileIndex]);
    lastAction = Action::UP;
    g++;

}

void Puzzle::moveBlankRight(const int blankIndex) {
    int tileIndex = blankIndex + 1;
    updateManhattanDistance(tileIndex, blankIndex);
    std::swap(state[blankIndex], state[tileIndex]);
    lastAction = Action::RIGHT;
    g++;

}

void Puzzle::moveBlankLeft(const int blankIndex) {
    int tileIndex = blankIndex - 1;
    updateManhattanDistance(tileIndex, blankIndex);
    std::swap(state[blankIndex], state[tileIndex]);
    lastAction = Action::LEFT;
    g++;



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
    heuristicCounter++;
    for (size_t i = 0; i < state.size(); i++) {
        int value = state[i] - '0';

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

    heuristicAccum+=totalDistance;
    return totalDistance;
}

void Puzzle::updateManhattanDistance(int tileIndex, int blankIndex){
    int tileValue = (state[tileIndex] - '0');
    int currentRow = tileIndex / gridSize;
    int currentCol = tileIndex % gridSize;
    int goalRow =  tileValue / gridSize;
    int goalCol = tileValue % gridSize;
    int prevDistance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);

    currentRow = blankIndex  / gridSize;
    currentCol = blankIndex  % gridSize;
    int curDistance = std::abs(currentRow - goalRow) + std::abs(currentCol - goalCol);
    int deltaDistance = curDistance - prevDistance;
    h += deltaDistance;


    heuristicAccum += h;
    heuristicCounter++;

}