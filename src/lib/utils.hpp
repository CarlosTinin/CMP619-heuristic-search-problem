#include <iostream>
using namespace std;

#ifndef UTILS_H
#define UTILS_H

struct Entry {
    string algorithm;
    vector< vector<int> > puzzles;
};

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

struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        string hash;
        for (int i : v) {
            hash += to_string(i);
        }
        return std::hash<string>()(hash);
    }
};

struct CompareHeuristicNode {
    bool operator() (Node const& n1, Node const& n2) {
        //return n1.heuristic_cost+n1.path_cost >= n2.heuristic_cost+n2.path_cost;
        if (n1.heuristic_cost > n2.heuristic_cost) {
            return true;
        } else if (n1.heuristic_cost == n2.heuristic_cost) {
            return n1.path_cost <= n2.path_cost;
        }

        return false;
    }
};

int heuristic(vector<int> state);

bool is_goal(vector<int> puzzle);

Node make_node(Node* parent, ACTIONS action, vector<int> state);

Node make_root_node(vector<int> state);

vector<int> swap(vector<int> puzzle, int first_position, int second_position);

void printEntry(Entry entry);

void printState(vector<int> vect);

#endif