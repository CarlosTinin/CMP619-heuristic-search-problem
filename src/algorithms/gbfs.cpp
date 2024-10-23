#include <iostream>
#include <unordered_set>

#include "../lib/gbfs.hpp"

Node gbfs(vector<int> puzzle, int* exp_nodes, double* heuristic_total) {
    priority_queue <Node, vector<Node>, CompareHeuristicNode > open; // min-heap

    Node init = make_root_node(puzzle);
    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;
    open.push(init);
    
    unordered_set< vector<int>, VectorHash > closed;

    while (!open.empty()) {
        Node n = open.top();
        open.pop();

        if (closed.find(n.state) == closed.end()) {
            closed.insert(n.state);
            
            if (is_goal(n.state)) {
                return n;
            }

            vector<Node> succ = successors(&n);

            for (int i = 0; i < succ.size(); i++) {
                open.push(succ[i]);
            }
        }

        *exp_nodes += 1;
        *heuristic_total += n.heuristic_cost;
    }

    return (Node) {};
}