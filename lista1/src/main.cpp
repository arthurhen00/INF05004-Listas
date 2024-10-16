#include "src/SearchAlg/BFS.hpp"
#include "src/Puzzle.hpp"

#include <iostream>
#include <vector>
#include <string>

#define EIGHT_PUZZLE 9
#define FIFTEEN_PUZZLE 16
// int getPuzzleType(int argc, char** argv){
//     if ((argc - 2) % 9 == 8) return FIFTEEN_PUZZLE;
//     if ((argc - 2) % 15 == 9) return EIGHT_PUZZLE;
// 
//     if((argc - 2) % 16 != 0 && (argc - 2) % 9 != 0) return 0;
//     for (int i = 2; i < 12; i++)
//     {
//         int value = atoi(argv[i]);
//         if (value > 8) {
//             return FIFTEEN_PUZZLE;
//         }
//     }
//     return EIGHT_PUZZLE;
// }
// 
// std::vector<Puzzle> getPuzzles(int puzzleType, int argc, char ** argv){
//     std::vector<Puzzle> puzzles;
//     std::string state;
//     for (int i = 2; i < argc; i++)
//     {
//         state += std::to_string(atoi(argv[i]));
//         if(i > 2 && (i-1) % puzzleType == 0){
//             puzzles.push_back(Puzzle(state,puzzleType));
//             state.clear();
//         }
//     }
//     return puzzles;
// }


int main(int argc, char** argv) {
    // int puzzleType = getPuzzleType(argc, argv);
    // if(puzzleType == 0){
    //     std::cerr << "Incorrect number of arguments! Usage main -[alg: bfs | idfs | astar | idastar | gbfs] [8 | 15 puzzle initial state: 9 * 0-8 | 16 * 0 - 15]";
    //     return EXIT_FAILURE;
    // }
    // std::vector<Puzzle> puzzles = getPuzzles(puzzleType,argc,argv);
    // //061742385, 502648173, 247036815
    // for (auto& p: puzzles){
    //     BFS(p);
    // }

    BFS(Puzzle({0,6,1,7,4,2,3,8,5}));
    BFS(Puzzle({5,0,2,6,4,8,1,7,3}));
    BFS(Puzzle({2,4,7,0,3,6,8,1,5}));

    printf("\n");

    return EXIT_SUCCESS;
}
