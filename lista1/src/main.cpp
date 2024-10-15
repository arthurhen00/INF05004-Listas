#include <iostream>
#include <vector>
#include <string>

#include "SearchAlg\BFS.hpp"
#include "Puzzle.hpp"
int main() {
    //061742385, 502648173, 247036815
    Puzzle p = Puzzle("502648173",9);
    BFS(p);



    return EXIT_SUCCESS;
}
