#include <iostream>
#include "utils.hpp"
#include "bfs.hpp"

#ifndef ASTAR_H
#define ASTAR_H

Node astar(vector<int> puzzle, int* exp_nodes, double* heuristic_total);

#endif