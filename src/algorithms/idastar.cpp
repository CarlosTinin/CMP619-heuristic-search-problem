#include <iostream>

#include "../lib/idastar.hpp"

const int INFINITE = 99999999;

Node idastar(vector<int> puzzle, int* exp_nodes, double* heuristic_total) {
    Node init = make_root_node(puzzle);

    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;

    int f_limit = init.heuristic_cost;
    pair<int, Node> result;

    while (f_limit != INFINITE) {
        result = recursive_idastar(init, f_limit, exp_nodes, heuristic_total);
        f_limit = result.first;

        if (!result.second.state.empty())
            return result.second;
    }

    return Node{};
}

pair<int, Node> recursive_idastar(Node n, int f_limit, int* exp_nodes, double* heuristic_total) {
    if (n.f() > f_limit) {
        return {n.f(), Node{}};
    }

    if (is_goal(n.state)) {
        return {INFINITE, n};
    }

    int next_limit = INFINITE;
    vector<Node> succ = successors(&n);
    *exp_nodes += 1;
    *heuristic_total += n.heuristic_cost;
    pair<int, Node> result;

    for (int i = 0; i < succ.size(); i++) {
        result = recursive_idastar(succ[i], f_limit, exp_nodes, heuristic_total);
        int rec_limit = result.first;
        
        if (!result.second.state.empty()) {
            return {INFINITE, result.second};
        }

        next_limit = min(next_limit, rec_limit);
    }

    return {next_limit, Node{}};
}