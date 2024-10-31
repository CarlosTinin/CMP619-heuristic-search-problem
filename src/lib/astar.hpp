#include <iostream>
#include "utils.hpp"
#include "bfs.hpp"

#ifndef ASTAR_H
#define ASTAR_H

Node astar(vector<int> puzzle, int* exp_nodes, double* heuristic_total);

Node astar_15(vector<int> puzzle, int* exp_nodes, double* heuristic_total);

vector<Node> successors_15(Node* actual);

#endif