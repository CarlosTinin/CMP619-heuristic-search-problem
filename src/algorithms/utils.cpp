#include <iostream>
#include "../lib/utils.hpp"

int heuristic(vector<int> state) {
    for (int i = 0; i < state.size(); i++) {
        // check row

        // check column
    }

    return 0;
}

void swap(vector<int>& puzzle, int first_position, int second_position) {
    int temp = puzzle[first_position];
    puzzle[first_position] = puzzle[second_position];
    puzzle[second_position] = temp;
}

Node make_root_node(vector<int> state) {
    Node node;
    node.state = state;
    node.parent = NULL;
    node.action = INITIAL;
    node.path_cost = 0;

    return node;
}

Node make_node(Node* parent, ACTIONS action, vector<int> state) {
    Node node;
    node.state = state;
    node.parent = parent;
    node.action = action;
    node.path_cost = parent->path_cost + 1;

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