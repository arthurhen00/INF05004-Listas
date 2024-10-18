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
        std::vector<char> state;
        static const std::vector<char> goalState;
        const static int gridSize = 3;
        int g;
        int h;
        int lastAction;

        Puzzle(std::vector<char> startState);
        Puzzle(std::vector<char> startState, int g, int lastAction);

        std::vector<Puzzle> getNeighbors() const;
        bool isGoal() const;

        void printPuzzle();

        int ManhattanDistance();
    
    private:
        void moveBlankDown(const int blankIndex);
        void moveBlankUp(const int blankIndex);
        void moveBlankRight(const int blankIndex);
        void moveBlankLeft(const int blankIndex);
        int findBlank() const;
}; 