#include <iostream>
#include "utils.hpp"

#ifndef BFS_H
#define BFS_H

struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        string hash;
        for (int i : v) {
            hash += to_string(i);
        }
        return std::hash<string>()(hash);
    }
};

Node bfs(vector<int> puzzle, int* exp_nodes);

vector<Node> successors(vector<int> &puzzle, Node &parent);

#endif