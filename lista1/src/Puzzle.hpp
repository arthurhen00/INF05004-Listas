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
        unsigned long long state;
        int g;
        int h;
        int lastAction;

        Puzzle(unsigned long long state, int size);

        std::vector<Puzzle> getNeighbors() const;
        bool isGoal() const;

        int ManhattanDistance();
        void updateManhattanDistance(int tileIndex, int blankIndex);
    
    private:
        void moveBlankDown(const int blankIndex);
        void moveBlankUp(const int blankIndex);
        void moveBlankRight(const int blankIndex);
        void moveBlankLeft(const int blankIndex);
        int findBlank() const;
}; 