#include <vector>
#include <string.h>
#include <stdexcept>

class State
{
private:
    State moveDown() const;
    State moveUp() const;
    State moveRight() const;
    State moveLeft() const;
    int findBlank() const;
public:
    char data[9];
    std::vector<State> getNeighbors() const;
    State(char inputData[9]);
};

State::State(char inputData[9])
{
    for (int i = 0; i < 9; ++i)
    {
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

State State::moveDown() const{
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex <= 5){
        std::swap(newData[blankIndex], newData[blankIndex + 3]);
    }
    return State(newData);
}
State State::moveUp() const{
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex > 2){
        std::swap(newData[blankIndex], newData[blankIndex - 3]);
    }
    return State(newData);
}
State State::moveRight() const{
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex % 3 != 2){
        std::swap(newData[blankIndex], newData[blankIndex + 1]);
    }
    return State(newData);
}
State State::moveLeft() const{
    int blankIndex = findBlank();
    char newData[9] ;
    std::copy(std::begin(data), std::end(data), newData);
    if(blankIndex % 3 != 0){
        std::swap(newData[blankIndex], newData[blankIndex - 1]);
    }
    return State(newData);
}

std::vector<State> State::getNeighbors() const{
    std::vector<State> neighbors;
    neighbors.push_back(moveUp());
    neighbors.push_back(moveLeft());
    neighbors.push_back(moveRight());
    neighbors.push_back(moveDown());
    return neighbors;
};