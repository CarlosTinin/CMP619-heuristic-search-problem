#include <iostream>
#include <cstring>
#include <chrono>

#include "./lib/bfs.hpp"
#include "./lib/idfs.hpp"

using chrono::high_resolution_clock;
using chrono::duration;

struct Entry {
    string algorithm;
    vector< vector<int> > puzzles;
};

void printState(vector<int> vect);

void astar() {
    printf("TODO: ASTAR");
}

void gbfs() {
    //priority_queue <Node, vector<Node>, CompareNode > open; // min-heap
    printf("TODO: GBFS");
}

void idastar() {
    printf("TODO: IDASTAR");
}

Entry parseArguments(int count, char* argv[]);

void printEntry(Entry entry);

int main(int argc, char* argv[]) {
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

            auto init = high_resolution_clock::now();
            Node result = bfs(entry.puzzles.at(i), &expanded_nodes);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << expanded_nodes << ",";
            cout << result.path_cost << ",";
            cout << elapsed_time.count() << ",";
            cout << "0,\n";
        }
    } else if (entry.algorithm == "-idastar") {
        idastar();
    } else if (entry.algorithm == "-idfs") {
        for (int i = 0; i < entry.puzzles.size(); i++ ) {
            int expanded_nodes = 0, cost = 0;

            auto init = high_resolution_clock::now();
            vector<int> result = idfs(entry.puzzles.at(i), &cost, &expanded_nodes);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << expanded_nodes << ",";
            cout << cost << ",";
            cout << elapsed_time.count() << ",";
            cout << "0,\n";
        }
    } else {
        gbfs();
    }

    //printEntry(entry);

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

void printEntry(Entry entry) {
    cout << "Alg: " << entry.algorithm << "\n";
    for (int i = 0; i < entry.puzzles.size(); i++) {
        printf("Entry: ");
        for (int j = 0; j < entry.puzzles.at(i).size(); j++) {
            cout << entry.puzzles.at(i).at(j) << " ";
        }
        printf("\n");
    }
}

void printState(vector<int> vect) {
    cout << "[";
    for (int i =0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "];\n";
}