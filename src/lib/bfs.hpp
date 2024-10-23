#include <iostream>
#include "utils.hpp"

#ifndef BFS_H
#define BFS_H

Node bfs(vector<int> puzzle, int* exp_nodes);

vector<Node> successors(Node* actual);

#endif