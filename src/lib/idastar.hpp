#include <iostream>
#include "utils.hpp"
#include "bfs.hpp"

#ifndef IDASTAR_H
#define IDASTAR_H

pair<int, Node>  recursive_idastar(Node n, int f_limit, int* exp_nodes);

Node idastar(vector<int> puzzle, int* exp_nodes);

#endif