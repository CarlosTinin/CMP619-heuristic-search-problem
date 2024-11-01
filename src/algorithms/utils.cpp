#include <iostream>
#include <cmath>
#include "../lib/utils.hpp"

int counter = 0;
int h_sum = 0;

int heuristic(vector<int> state) {
    counter++;
    int heuristicSum = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state.at(i) != 0) { // remove blank from heuristic calculation
            int column = abs((state.at(i) % 3) - (i % 3)); // checking column
            int row = abs((floor(state.at(i) / 3) - floor(i / 3))); // checking row

            heuristicSum += column+row;
        }
    }

    h_sum += heuristicSum;

    return heuristicSum;
}

int heuristic_15(vector<int> state) {
    counter++;
    int heuristicSum = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state.at(i) != 0) { // remove blank from heuristic calculation
            int column = abs((state.at(i) % 4) - (i % 4)); // checking column
            int row = abs((floor(state.at(i) / 4) - floor(i / 4))); // checking row

            heuristicSum += column+row;
        }
    }

    h_sum += heuristicSum;
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
    node.insertion_order = 0;
    node.heuristic_cost = heuristic(node.state);

    return node;
}

Node make_root_node_15(vector<int> state) {
    Node node;
    node.state = state;
    node.parent = NULL;
    node.action = INITIAL;
    node.path_cost = 0;
    node.insertion_order = 0;
    node.heuristic_cost = heuristic_15(node.state);

    return node;
}

Node make_node(Node* parent, ACTIONS action, vector<int> state) {
    Node node;
    node.state = state;
    node.parent = parent;
    node.insertion_order = 0;
    node.action = action;
    node.path_cost = parent->path_cost + 1;
    node.heuristic_cost = heuristic(node.state);

    return node;
}

Node make_node_15(Node* parent, ACTIONS action, vector<int> state) {
    Node node;
    node.state = state;
    node.parent = parent;
    node.action = action;
    node.path_cost = parent->path_cost + 1;
    node.heuristic_cost = heuristic_15(node.state);

    return node;
}

bool is_goal(vector<int> puzzle) {
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

int vectToInt(vector<int> vect) {
    int result = 0;
    for (auto d : vect) {
        result = result * 10 + d;
    }
    return result;
}

float getSum() {
    float result = 0;
    if (h_sum != 0)
        result = (float) h_sum / (float) counter;
    
    h_sum = 0;
    counter = 0;

    return result;
}