#include "src/SearchAlg/Search.hpp"
#include "src/Puzzle.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

char numToChar(int num) {
    if (num >= 10 && num <= 15) {
        return 'a' + (num - 10);
    }
    return '0' + num;
}

std::vector<char> parseState(const std::string& state) {
    std::vector<char> result;
    std::istringstream stream(state);
    std::string token;

    while (std::getline(stream, token, ' ')) {
        int num = std::stoi(token);
        result.push_back(numToChar(num));
    }

    return result;
}

std::string trim(const std::string& str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    return result;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: ./main <algoritmo> <estados>\n");
        return EXIT_FAILURE;
    }

    std::string alg = argv[1];
    std::string states;
    for (int i = 2; i < argc; ++i) {
        states += argv[i];
        if (i < argc - 1) {
            states += ' ';
        }
    }

    std::istringstream stateStream(states);
    std::string state;

    Search search = Search();

    while (std::getline(stateStream, state, ',')) {
        state = trim(state);
        std::vector<char> stateVector = parseState(state);
        Puzzle puzzle(stateVector);

        if (alg.compare("-astar") == 0) {
            search.AStar(puzzle);
        } else if (alg.compare("-bfs") == 0) {
            search.BFS(puzzle);
        } else if (alg.compare("-idastar") == 0) {
            search.IDAStar(puzzle);
        } else if (alg.compare("-idfs") == 0) {
            search.IDFS(puzzle);
        } else if (alg.compare("-gbfs") == 0) {
            search.GBFS(puzzle);
        }
    }

    return EXIT_SUCCESS;
}
