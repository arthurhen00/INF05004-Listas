#pragma once

#include <vector>
#include <string>

enum Action {
    UNSET,
    UP,
    DOWN,
    RIGHT,
    LEFT
};
class Puzzle {
    public:
        Puzzle(std::string startingState, unsigned int puzzleSize);
        Puzzle(const char startingState[], unsigned int puzzleSize);
        std::vector<Puzzle> getNeighbors() const;
        int getManhattanDistance() const;
        bool isGoal() const;

        static std::string goalState;
        std::string currentState;
        unsigned int size;
        int solutionLength;
        int lastAction;
    
        friend std::ostream& operator<<(std::ostream& os, const Puzzle& obj);

    private:
        
        Puzzle(std::string startingState, unsigned int puzzleSize, int length, int action);
        Puzzle(const char startingState[], unsigned int puzzleSize, int length, int action);
        void moveDown();
        void moveUp();
        void moveRight();
        void moveLeft();
        int findBlank() const;
}; 