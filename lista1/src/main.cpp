#include "src/Search.hpp"
#include "src/Puzzle.hpp"

#include <iostream>
#include <vector>
#include <string>


#include <bitset>
#include <type_traits>
template <typename T>
void printBinary(T number) {
    constexpr size_t numBits = sizeof(T) * 8;
    std::bitset<numBits> binary(number);     
    std::cout << binary << std::endl << std::endl;
}
void print4BitChunks(unsigned long long number) {
    const int CHUNK_SIZE = 4;  
    const int TOTAL_BITS = 64;     
    const unsigned long long MASK = 0xF; 

    for (int i = 0; i < TOTAL_BITS; i += CHUNK_SIZE) {
        unsigned int chunk = (number >> i) & MASK;
        std::cout << chunk << " ";
    }
    std::cout << std::endl;
}


unsigned long long encodeState(const std::vector<char>& state) {
    unsigned long long idx = 0;
    for (unsigned long long  i = 0; i < state.size(); ++i) {
        unsigned long long val = state[i] - '0';             
        val = static_cast<int>(val);
        idx |= val << (i * 4);
    }
    return idx;
}


#define EIGHT_PUZZLE 9
#define FIFTEEN_PUZZLE 16
int getPuzzleType(int argc, char** argv){
    if ((argc - 2) % 9 == 8) return FIFTEEN_PUZZLE;
    if ((argc - 2) % 15 == 9) return EIGHT_PUZZLE;

    if((argc - 2) % 16 != 0 && (argc - 2) % 9 != 0) return 0;
    for (int i = 2; i < 12; i++)
    {
        int value = atoi(argv[i]);
        if (value > 8) {
            return FIFTEEN_PUZZLE;
        }
    }
    return EIGHT_PUZZLE;
}

std::vector<Puzzle> getPuzzles(int puzzleType, int argc, char ** argv){
    std::vector<Puzzle> puzzles;
    std::vector<char> state;
    for (int i = 2; i < argc; i++)
    {
        int value = atoi(argv[i]);
      
         if (value >= 0 && value <= 15) {
            value = value + '0'; // '0' to '9'
            state.push_back(value);
            
        } else {
            std::cerr << "Error: Value out of range (0-15): " << value << std::endl;
            return puzzles;
        }

         if(i > 2 && (i-1) % puzzleType == 0){
            puzzles.push_back(Puzzle(encodeState(state),puzzleType));
            state.clear();
        }
    }
    return puzzles;
}

int main(int argc, char** argv) {
     int puzzleType = getPuzzleType(argc, argv);
     if(puzzleType == 0){
         std::cerr << "Incorrect number of arguments! Usage main -[alg: bfs | idfs | astar | idastar | gbfs] [8 | 15 puzzle initial state: 9 * (0 - 8) | 16 * (0 - 15)]";
         return EXIT_FAILURE;
     }
     Search search = Search();
     std::vector<Puzzle> puzzles = getPuzzles(puzzleType,argc,argv);

    
     std::string algorithm = argv[1];
     if (algorithm == "-bfs") {
        for (auto& p : puzzles)
        {
            search.BFS(p);
        }
    } else if (algorithm == "-idfs") {
        for(auto& p : puzzles)
        {
            search.IDFS(p);
        }
    } else if (algorithm == "-astar") {
        for(auto& p : puzzles)
        {
            search.AStar(p);
        }
    } else if (algorithm == "-idastar") {
        for(auto& p : puzzles)
        {
            search.IDAStar(p);
        }
    } else if (algorithm == "-gbfs") {
        for(auto& p : puzzles)
        {
            search.GBFS(p);
        }
    } else {
        std::cerr << "Invalid algorithm. Available algorithms are: -bfs, -idfs, -astar, -idastar, -gbfs" << std::endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
