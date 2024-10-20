#include <iostream>
#include "utils.hpp"

#ifndef GBFS_H
#define GBFS_H

struct CompareHeuristicNode {
    bool operator() (Node const& n1, Node const& n2) {
        return n1.heuristic_cost > n2.heuristic_cost;
    }
};

#endif