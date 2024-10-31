#include <iostream>
#include <unordered_set>
#include <deque>
#include <stdlib.h>
#include "../lib/bfs.hpp"

vector<Node> successors(Node* actual) { // works only for 8puzzle
    vector<Node> result;
    int blank = 0;
    for (int i = 0; i < actual->state.size(); i++) {
        if (actual->state[i] == 0) {
            blank = i;
            break;
        }
    }

    vector<pair<int, int>> moves = {
        {blank-3, UP},
        {blank-1, LEFT},
        {blank+1, RIGHT},
        {blank+3, DOWN}
    };

    for (const auto& pair: moves) {
        int new_blank = pair.first;
        ACTIONS direction = (ACTIONS) pair.second;
        if (new_blank >= 0 && new_blank < 9 && !((blank % 3 == 0 && direction == LEFT) || (blank % 3 == 2 && direction == RIGHT))) {
            if (actual->parent->state.at(new_blank) != 0) {
                vector<int> newState = actual->state;
                Node* parent = (Node *) malloc(sizeof(Node));
                *parent = *actual;
                result.push_back(make_node(parent, direction, swap(newState, new_blank, blank)));
            }
        }
    }

    return result;
}

Node bfs(vector<int> puzzle, int* exp_nodes) {
    if (is_goal(puzzle)) {
        return (Node) {};
    }
    deque<Node> open;

    Node init = make_root_node(puzzle);

    Node temp;
    temp.state = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; 
    temp.path_cost = 0;
    init.parent = &temp;

    open.push_back(init);
    unordered_set< vector<int>, VectorHash > closed;
    closed.insert(puzzle);

    while (!open.empty()) {
        Node n = open.front();
        open.pop_front();

        vector<Node> succ = successors(&n);
        *exp_nodes+=1;

        for (int i = 0; i < succ.size(); i++) {
            if (is_goal(succ[i].state)) {
                return succ[i];
            }

            if (closed.find(succ[i].state) == closed.end()) {
                closed.insert(succ[i].state);
                open.push_back(succ[i]);
            }
        }
    }

    return (Node) {};
}