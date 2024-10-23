#include <iostream>
#include "../lib/utils.hpp"

int heuristic(vector<int> state) {
    int heuristicSum = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state.at(i) != 0) { // remove blank from heuristic calculation
            int column = abs((state.at(i) % 3) - (i % 3)); // checking column
            int row = abs((floor(state.at(i) / 3) - (i / 3))); // checking row

            heuristicSum += column+row;
        }
    }

    return heuristicSum;
}

vector<int> swap(vector<int> puzzle, int first_position, int second_position) {
    vector<int> newPuzzle = puzzle;
    int temp = newPuzzle[first_position];
    newPuzzle[first_position] = newPuzzle[second_position];
    newPuzzle[second_position] = temp;

    return newPuzzle;
}

Node make_root_node(vector<int> state) {
    Node node;
    node.state = state;
    node.parent = NULL;
    node.action = INITIAL;
    node.path_cost = 0;
    node.heuristic_cost = heuristic(node.state);

    return node;
}

Node make_node(Node* parent, ACTIONS action, vector<int> state) {
    Node node;
    node.state = state;
    node.parent = parent;
    node.action = action;
    node.path_cost = parent->path_cost + 1;
    node.heuristic_cost = heuristic(node.state);

    return node;
}

bool is_goal(vector<int> puzzle) { // TODO improve preformance
    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle.at(i) != i) {
            return false;
        }
    }
    return true;
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
    cout << "];";
}