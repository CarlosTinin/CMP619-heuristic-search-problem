#include <iostream>
#include "utils.hpp"
#include "bfs.hpp"

#ifndef GBFS_H
#define GBFS_H

Node gbfs(vector<int> puzzle, int* exp_nodes, double* heuristic_total);

#endif