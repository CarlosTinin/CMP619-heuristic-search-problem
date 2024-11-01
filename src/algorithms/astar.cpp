#include <unordered_set>
#include <iostream>
#include <queue>
#include <map>

#include "../lib/astar.hpp"

Node astar(vector<int> puzzle, int* exp_nodes) {
    priority_queue <Node, vector<Node>, CompareHeuristicAndPathCostNode > open; // min-heap

    Node init = make_root_node(puzzle);
    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;
    open.push(init);
    int insert_order = 0;
    //map< vector<int>, int> distances; // with reopening
    unordered_set< vector<int>, VectorHash > closed; // without reopening
    while (!open.empty()) {
        Node n = open.top();
        open.pop();

        //if (distances.find(n.state) == distances.end() || n.path_cost < distances[n.state]) {
        if (closed.find(n.state) == closed.end()) {
            //distances[n.state] = n.path_cost;
            closed.insert(n.state);

            if (is_goal(n.state)) {
                return n;
            }
            
            *exp_nodes += 1;

            vector<Node> succ = successors(&n);

            for (int i = 0; i < succ.size(); i++) {
                succ[i].insertion_order = insert_order++;
                open.push(succ[i]);
            }
        }

    }

    return (Node) {};
}

Node astar_15(vector<int> puzzle, int* exp_nodes) {
    priority_queue <Node, vector<Node>, CompareHeuristicAndPathCostNode > open; // min-heap

    Node init = make_root_node_15(puzzle);
    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;
    int insert_order = 0;
    open.push(init);

    const std::chrono::seconds timeLimit(30);
    auto start = std::chrono::steady_clock::now();
    
    //map< vector<int>, int> distances; // with reopening
    unordered_set< vector<int>, VectorHash > closed; // without reopening
    
    while (!open.empty()) {
        Node n = open.top();
        open.pop();
    
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - start;

        if (elapsed > timeLimit) {
            cout << "Operation canceled: Time limit exceeded (30 seconds)." << endl;
            return (Node){};
        }

        //if (distances.find(n.state) == distances.end() || n.path_cost < distances[n.state]) {
        if (closed.find(n.state) == closed.end()) {
            //distances[n.state] = n.path_cost;
            closed.insert(n.state);

            if (is_goal(n.state)) {
                return n;
            }
            
            *exp_nodes += 1;

            vector<Node> succ = successors_15(&n);

            for (int i = 0; i < succ.size(); i++) {
                succ[i].insertion_order = insert_order++;
                open.push(succ[i]);
            }
        }

    }

    return (Node) {};
}

vector<Node> successors_15(Node* actual) {
    vector<Node> result;
    int blank = 0;
    for (int i = 0; i < actual->state.size(); i++) {
        if (actual->state[i] == 0) {
            blank = i;
            break;
        }
    }

    vector<pair<int, int>> moves = {
        {blank-4, UP},
        {blank-1, LEFT},
        {blank+1, RIGHT},
        {blank+4, DOWN}
    };

    for (const auto& pair: moves) {
        int new_blank = pair.first;
        ACTIONS direction = (ACTIONS) pair.second;
        if (new_blank >= 0 && new_blank < 16 && !((blank % 4 == 0 && direction == LEFT) || (blank % 4 == 3 && direction == RIGHT))) {
            if (actual->parent->state.at(new_blank) != 0) {
                vector<int> newState = actual->state;
                Node* parent = (Node *) malloc(sizeof(Node));
                *parent = *actual;
                result.push_back(make_node_15(parent, direction, swap(newState, new_blank, blank)));
            }
        }
    }

    return result;
}