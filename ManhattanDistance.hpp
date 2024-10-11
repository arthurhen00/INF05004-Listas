#include "Heuristic.hpp"

class ManhattanDistance : public Heuristic {
    public: 
        int Calculate(const std::vector<int>& state) const override;
        
    private:
};