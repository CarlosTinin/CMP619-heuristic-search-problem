#include <iostream>
#include <cstring>
#include <chrono>

#include "./lib/bfs.hpp"
#include "./lib/gbfs.hpp"
#include "./lib/idfs.hpp"

using chrono::high_resolution_clock;
using chrono::duration;

void printState(vector<int> vect);

void astar() {
    printf("TODO: ASTAR");
}

void idastar() {
    printf("TODO: IDASTAR");
}

Entry parseArguments(int count, char* argv[]);

void printEntry(Entry entry);

int main(int argc, char* argv[]) { // refactor here
    if (argc < 11) {
        cout << "Invalid entry size.";
        return 0;
    }
    Entry entry = parseArguments(argc, argv);

    if (entry.algorithm == "-astar") {
        astar();
    } else if (entry.algorithm == "-bfs") {
        for (int i = 0; i < entry.puzzles.size(); i++ ) {
            int expanded_nodes = 0;
            vector<int> puzzle = entry.puzzles.at(i);

            auto init = high_resolution_clock::now();
            Node result = bfs(puzzle, &expanded_nodes);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << expanded_nodes << ",";
            cout << result.path_cost << ",";
            cout << elapsed_time.count() << ",";
            cout << "0,";
            cout << heuristic(puzzle) << endl;
        }
    } else if (entry.algorithm == "-idastar") {
        idastar();
    } else if (entry.algorithm == "-idfs") {
        for (int i = 0; i < entry.puzzles.size(); i++ ) {
            int expanded_nodes = 0, cost = 0;
            vector<int> puzzle = entry.puzzles.at(i);

            auto init = high_resolution_clock::now();
            vector<int> result = idfs(puzzle, &cost, &expanded_nodes);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << expanded_nodes << ",";
            cout << cost << ",";
            cout << elapsed_time.count() << ",";
            cout << "0,";
            cout << heuristic(puzzle) << endl;
        }
    } else { // GBFS
        for (int i = 0; i < entry.puzzles.size(); i++ ) {
            int expanded_nodes = 0;
            double heuristic_total = 0;
            vector<int> puzzle = entry.puzzles.at(i);

            auto init = high_resolution_clock::now();
            Node result = gbfs(puzzle, &expanded_nodes, &heuristic_total);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << fixed;
            cout << expanded_nodes << ",";
            cout << result.path_cost << ",";
            cout << elapsed_time.count() << ",";
            cout << heuristic_total/expanded_nodes << ",";
            cout << heuristic(puzzle) << endl;
        }
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