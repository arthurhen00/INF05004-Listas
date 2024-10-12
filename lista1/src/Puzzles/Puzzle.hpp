#pragma once

#include <vector>

class Puzzle {
    public:
        Puzzle(const std::vector<int>& initialState) : state(initialState) {}
        virtual ~Puzzle() {}

        virtual int getGridSize() const = 0;
        virtual std::vector<int> getGoalState() const = 0;
        const std::vector<int>& getState() const { return state; }

    protected:
        std::vector<int> state;
};