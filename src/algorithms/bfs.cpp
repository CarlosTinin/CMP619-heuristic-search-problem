#include <iostream>
#include <unordered_set>
#include "../lib/bfs.hpp"

vector<Node> successors(vector<int> &puzzle, Node &parent) { // works only for 8puzzle
    vector<Node> result;
    int blank = 0;
    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle[i] == 0) {
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
        int direction = pair.second;
        if (new_blank >= 0 && new_blank < 9 && !((blank % 3 == 0 && direction == LEFT) || (blank % 3 == 2 && direction == RIGHT))) {
            if (parent.state.at(new_blank) != 0) {
                swap(puzzle, new_blank, blank);
                result.push_back(make_node(&parent, UP, puzzle));
                swap(puzzle, blank, new_blank);
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
        vector<Node> succ = successors(n.state, n);
        *exp_nodes+=1;

        for (int i = 0; i < succ.size(); i++) {
            if (is_goal(succ[i].state)) {
                return succ[i];
            }

            if (closed.find(succ[i].state) == closed.end()) {
                closed.insert(succ[i].state);
                open.push_back(std::move(succ[i]));
            }
        }
    }

    return (Node) {};
}