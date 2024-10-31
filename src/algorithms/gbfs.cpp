#include <iostream>
#include <unordered_set>
#include <queue>

#include "../lib/gbfs.hpp"

Node gbfs(vector<int> puzzle, int* exp_nodes) {
    priority_queue <Node, vector<Node>, CompareHeuristicNode > open; // min-heap

    Node init = make_root_node(puzzle);
    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    temp.heuristic_cost = 0;
    init.parent = &temp;
    open.push(init);
    
    unordered_set< vector<int>, VectorHash > closed;

    while (!open.empty()) {
        Node n = open.top();
        open.pop();

        if (closed.find(n.state) == closed.end()) {
            //printState(n.state);
            //cout << " --> ";
            closed.insert(n.state);

            if (is_goal(n.state)) {
                return n;
            }

            *exp_nodes += 1;
            
            vector<Node> succ = successors(&n);

            for (int i = 0; i < succ.size(); i++) {
                // cout << "(";
                // printState(succ[i].state);
                // cout << " [ ";
                // cout << succ[i].heuristic_cost << ", " << succ[i].path_cost;
                // cout << " ]) ";
                open.push(succ[i]);
            }
            //cout << endl;
        }
    }

    return (Node) {};
}