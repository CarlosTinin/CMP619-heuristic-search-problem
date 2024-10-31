#include <iostream>
#include <vector>
using namespace std;

#ifndef UTILS_H
#define UTILS_H

struct Entry {
    string algorithm;
    vector< vector<int> > puzzles;
};

enum ACTIONS {
    UP,
    LEFT,
    RIGHT,
    DOWN,
    INITIAL
};

struct Node {
    vector<int> state;
    Node* parent;
    enum ACTIONS action;
    int path_cost;
    int heuristic_cost;
    int insertion_order;

    int f() {
        return path_cost+heuristic_cost;
    }
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
        if (n1.heuristic_cost > n2.heuristic_cost) { // min: valor - h
            return true;
        } else if (n1.heuristic_cost == n2.heuristic_cost) {
            return n1.path_cost + n1.action <= n2.path_cost + n2.action; // max: valor - g / LIFO
        }

        return false;
    }
};

void printState(vector<int> vect);

int vectToInt(vector<int> vect);

struct CompareHeuristicAndPathCostNode {
    bool operator() (Node const& n1, Node const& n2) {
        int f1 = n1.heuristic_cost + n1.path_cost;
        int f2 = n2.heuristic_cost + n2.path_cost;

        if (f1 > f2) { // min: valor - f
            return true;
        } else if (f1 == f2) {
            if (n1.heuristic_cost > n2.heuristic_cost) { // min: valor h
                return true;
            } else if (n1.heuristic_cost == n2.heuristic_cost) { 
                return n1.insertion_order < n2.insertion_order; // LIFO
            }
        }

        return false;
    }
};

int heuristic(vector<int> state);

int heuristic_15(vector<int> state);

bool is_goal(vector<int> puzzle);

Node make_node(Node* parent, ACTIONS action, vector<int> state);

Node make_node_15(Node* parent, ACTIONS action, vector<int> state);

Node make_root_node(vector<int> state);

Node make_root_node_15(vector<int> state);

vector<int> swap(vector<int> puzzle, int first_position, int second_position);

void printEntry(Entry entry);

#endif