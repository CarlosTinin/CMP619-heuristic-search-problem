#include <iostream>
#include <cstring>
#include <chrono>
#include <iomanip>

#include "./lib/bfs.hpp"
#include "./lib/gbfs.hpp"
#include "./lib/idfs.hpp"
#include "./lib/astar.hpp"
#include "./lib/idastar.hpp"

using chrono::high_resolution_clock;
using chrono::duration;

Entry parseArguments(int count, char* argv[]);

void printResult(int expanded_nodes, int cost, double elapsed_time, float heuristic_total, int initial_heuristic);

int main(int argc, char* argv[]) {
    if (argc < 11) {
        cout << "Invalid entry size.";
        return 0;
    }
    Entry entry = parseArguments(argc, argv);

    for (int i = 0; i < entry.puzzles.size(); i++ ) {
        int expanded_nodes = 0, cost = 0;
        duration<double> elapsed_time;
        vector<int> puzzle = entry.puzzles.at(i);
        
        if (entry.algorithm == "-astar") {
            Node result = Node{};
            if (entry.puzzles.at(i).size() == 9) {
                auto init = high_resolution_clock::now();
                Node result = astar(puzzle, &expanded_nodes);
                auto finish = high_resolution_clock::now();
                elapsed_time = finish - init;
                cost = result.path_cost;
            } else {
                auto init = high_resolution_clock::now();
                Node result = astar_15(puzzle, &expanded_nodes);
                auto finish = high_resolution_clock::now();
                elapsed_time = finish - init;
                cost = result.path_cost;
            }
        } else if (entry.algorithm == "-bfs") {
            auto init = high_resolution_clock::now();
            Node result = bfs(puzzle, &expanded_nodes);
            auto finish = high_resolution_clock::now();
            getSum(); // resets counters
            cost = result.path_cost;
            elapsed_time = finish - init;
        } else if (entry.algorithm == "-idastar") {
            auto init = high_resolution_clock::now();
            Node result = idastar(puzzle, &expanded_nodes);
            auto finish = high_resolution_clock::now();

            cost = result.path_cost;
            elapsed_time = finish - init;
        } else if (entry.algorithm == "-idfs") {
            auto init = high_resolution_clock::now();
            vector<int> result = idfs(puzzle, &cost, &expanded_nodes);
            auto finish = high_resolution_clock::now();
            getSum(); // resets counters
            elapsed_time = finish - init;
        } else {
            auto init = high_resolution_clock::now();
            Node result = gbfs(puzzle, &expanded_nodes);
            auto finish = high_resolution_clock::now();

            cost = result.path_cost;
            elapsed_time = finish - init;
        }

        printResult(expanded_nodes, cost, elapsed_time.count(), getSum(), heuristic(puzzle));        
    }

    return 0;
}

Entry parseArguments(int count, char* argv[]) {
    Entry entry;

    entry.algorithm = argv[1];
    vector<int> puzzle;

    for (int i = 0; i < count - 2; i++) {
        if (!strchr(argv[i+2], ',')) {
            puzzle.push_back(atoi(argv[i+2]));
        } else {
            puzzle.push_back(atoi(argv[i+2]));
            entry.puzzles.push_back(puzzle);
            puzzle.clear();
        }
    }

    if (!puzzle.empty())
        entry.puzzles.push_back(puzzle);

    return entry;
}

void printResult(int expanded_nodes, int cost, double elapsed_time, float heuristic_avg, int initial_heuristic) {
    cout << expanded_nodes << ",";
    cout << cost << ",";
    cout << elapsed_time << ",";
    
    if (heuristic_avg != 0) {
        cout << fixed << setprecision(5) << heuristic_avg << ",";
    } else {
        cout << "0,";
    }

    cout << initial_heuristic << endl;
    cout.unsetf(ios::fixed);
}