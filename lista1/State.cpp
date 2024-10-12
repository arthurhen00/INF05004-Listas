#include <vector>
#include <string.h>
#include <stdexcept>

class State {
    public:
        State(char inputData[9], int length = 0, int heuristic = 0);

        std::vector<State> getNeighbors() const;
        bool isGoal() const;

        char data[9];
        int solutionLength;
        int heuristicValue;

    private:
        State moveDown() const;
        State moveUp() const;
        State moveRight() const;
        State moveLeft() const;
        int findBlank() const;
};

State::State(char inputData[9], int length, int heuristic) : solutionLength(length), heuristicValue(heuristic) {
    for (int i = 0; i < 9; ++i) {
        data[i] = inputData[i];
    }
}

int State::findBlank() const {
    for (size_t i = 0; i < 9; ++i) {
        if (data[i] == ' ') {
            return i;
        }
    }
    throw std::runtime_error("Blank space not found in the state.");
}

State State::moveDown() const {
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex <= 5){
        std::swap(newData[blankIndex], newData[blankIndex + 3]);
    }
    return State(newData, solutionLength + 1);
}

State State::moveUp() const {
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex > 2){
        std::swap(newData[blankIndex], newData[blankIndex - 3]);
    }
    return State(newData, solutionLength + 1);
}

State State::moveRight() const {
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex % 3 != 2){
        std::swap(newData[blankIndex], newData[blankIndex + 1]);
    }
    return State(newData, solutionLength + 1);
}

State State::moveLeft() const {
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex % 3 != 0){
        std::swap(newData[blankIndex], newData[blankIndex - 1]);
    }
    return State(newData, solutionLength + 1);
}

std::vector<State> State::getNeighbors() const {
    std::vector<State> neighbors;
    neighbors.push_back(moveUp());
    neighbors.push_back(moveLeft());
    neighbors.push_back(moveRight());
    neighbors.push_back(moveDown());
    return neighbors;
};

bool State::isGoal() const {
    char goalState[9] = {' ', '1', '2', '3', '4', '5', '6', '7', '8'};
    return (memcmp(data, goalState, 9) == 0);
}