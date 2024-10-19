#include "src/SearchAlg/Search.hpp"
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

    // 10 a
    // 11 b
    // 12 c
    // 13 d
    // 14 e
    // 15 f

    Puzzle puzzle1 = Puzzle({'0','6','1','7','4','2','3','8','5'});
    Puzzle puzzle2 = Puzzle({'5','0','2','6','4','8','1','7','3'});
    Puzzle puzzle3 = Puzzle({'2','4','7','0','3','6','8','1','5'});
    Puzzle puzzle4 = Puzzle({'7','b','8','3','e','0','6','f','1','4','d','9','5','c','2','a'});
    Puzzle puzzle5 = Puzzle({'c','9','0','6','8','3','5','e','2','4','b','7','a','1','f','d'});
    Puzzle puzzle6 = Puzzle({'d','0','9','c','b','6','3','5','f','8','1','a','4','e','2','7'});
    
    Search search = Search();
    std::cout << std::endl << "Astar:" << std::endl;
    
    search.AStar(puzzle1);
    search.AStar(puzzle2);
    search.AStar(puzzle3);

    std::cout << std::endl << "BFS:" << std::endl;
    search.BFS(puzzle1);
    search.BFS(puzzle2);
    search.BFS(puzzle3);

    std::cout << std::endl << "IDAStar:" << std::endl;
    
    search.IDAStar(puzzle1);
    search.IDAStar(puzzle2);
    search.IDAStar(puzzle3);

    std::cout << std::endl << "IDFS:" << std::endl;
    
    search.IDFS(puzzle1);
    search.IDFS(puzzle2);
    search.IDFS(puzzle3);

    std::cout << std::endl << "GBFS:" << std::endl;

    search.GBFS(puzzle1);
    search.GBFS(puzzle2);
    search.GBFS(puzzle3);
  
    std::cout << std::endl << "Astar 15:" << std::endl;

    search.AStar(puzzle4);
    search.AStar(puzzle5);
    search.AStar(puzzle6);
    


    return EXIT_SUCCESS;
}
