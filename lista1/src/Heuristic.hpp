#include <vector>

class Heuristic {
    public:
        virtual int Calculate(const std::vector<int>& state) const = 0;
        virtual ~Heuristic() {}

    private:
};