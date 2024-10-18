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
        std::vector<int> state;
        static const std::vector<int> goalState;
        const static int gridSize = 3;
        int g;
        int h;
        int lastAction;

        Puzzle(std::vector<int> startState);
        Puzzle(std::vector<int> startState, int g, int lastAction);

        std::vector<Puzzle> getNeighbors() const;
        bool isGoal() const;

        void printPuzzle();

        int ManhattanDistance(std::vector<int> state);
    
    private:
        void moveBlankDown(const int blankIndex);
        void moveBlankUp(const int blankIndex);
        void moveBlankRight(const int blankIndex);
        void moveBlankLeft(const int blankIndex);
        int findBlank() const;
}; 