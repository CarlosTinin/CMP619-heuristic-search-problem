#include <iostream>
#include <map>
#include <unordered_set>

#include "../lib/astar.hpp"

Node astar(vector<int> puzzle, int* exp_nodes, double* heuristic_total) {
    priority_queue <Node, vector<Node>, CompareHeuristicAndPathCostNode > open; // min-heap

    Node init = make_root_node(puzzle);
    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;
    open.push(init);
    
    map< vector<int>, int> distances; // with reopening
    //unordered_set< vector<int>, VectorHash > closed; // without reopening
    while (!open.empty()) {
        Node n = open.top();
        open.pop();

        if (distances.find(n.state) == distances.end() || n.path_cost < distances[n.state]) {
        //if (closed.find(n.state) == closed.end()) {
            distances[n.state] = n.path_cost;
            //closed.insert(n.state);

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