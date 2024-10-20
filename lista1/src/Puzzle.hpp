#pragma once

#include <vector>
#include <string>

extern size_t heuristicAccum;
extern size_t heuristicCounter;
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
        int gridSize;
        int g;
        int h;
        int lastAction;

        Puzzle(std::vector<char> startState);

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