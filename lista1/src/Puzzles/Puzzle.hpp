#pragma once

#include <vector>

class Puzzle {
    public:
        Puzzle(const std::vector<int>& initialState,
               const std::vector<int>& goalState) 
        : startState_(initialState),
        goalState_(goalState) {}
        virtual ~Puzzle() {}

        virtual int getGridSize() const = 0;
        const std::vector<int>& getStartState() const { return startState_; }
        const std::vector<int>& getGoalState() const { return goalState_; }

    protected:
        std::vector<int> startState_;
        std::vector<int> goalState_;
};