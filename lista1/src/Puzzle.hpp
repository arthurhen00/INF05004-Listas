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
        Puzzle(std::string startingState, unsigned int size);
        Puzzle(const char startingState[], unsigned int size);
        std::vector<Puzzle> getNeighbors() const;
        int getManhattanDistance() const;
        bool isGoal() const;

        static std::string goalState;
        std::string currentState;
        unsigned int puzzleSize;
        unsigned int gridSize;
        int solutionLength;
        int lastAction;
    
        friend std::ostream& operator<<(std::ostream& os, const Puzzle& obj);

    private:
        
        Puzzle(std::string startingState, unsigned int size, int length, int action);
        Puzzle(const char startingState[], unsigned int size, int length, int action);
        void moveBlankDown();
        void moveBlankUp();
        void moveBlankRight();
        void moveBlankLeft();
        int findBlank() const;
}; 