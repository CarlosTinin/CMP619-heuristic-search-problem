#include <iostream>
#include "utils.hpp"

#ifndef IDFS_H
#define IDFS_H

const int MAX_DEPTH = 23;

vector<int> recursive_idfs(vector<int>& puzzle, int* cost, int* exp_nodes, int depth_limit, vector<int> parent);

vector<int> idfs(vector<int>& puzzle, int* cost, int* exp_nodes);

vector<vector<int>> successors(vector<int>& puzzle, vector<int> &parent);

#endif