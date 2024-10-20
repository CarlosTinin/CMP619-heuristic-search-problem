#include <iostream>
using namespace std;

#ifndef UTILS_H
#define UTILS_H

enum ACTIONS {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    INITIAL
};

struct Node {
    vector<int> state;
    Node* parent;
    enum ACTIONS action;
    int path_cost;
    int heuristic_cost;
};

int heuristic(vector<int> state);

bool is_goal(vector<int> puzzle);

Node make_node(Node* parent, ACTIONS action, vector<int> state);

Node make_root_node(vector<int> state);

void swap(vector<int>& puzzle, int first_position, int second_position);

#endif