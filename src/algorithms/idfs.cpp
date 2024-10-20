#include <iostream>
#include "../lib/idfs.hpp"

vector<int> recursive_idfs(vector<int>& puzzle, int* cost, int* exp_nodes, int depth_limit, vector<int> parent) {
    if (is_goal(puzzle)) {
        return puzzle;
    }

    if (depth_limit > 0) {
        vector<vector<int>> succ = successors(puzzle, parent);
        *exp_nodes+=1;

        for(int i = 0; i < succ.size(); i++) {
            vector<int> solution = recursive_idfs(succ[i], cost, exp_nodes, depth_limit-1, puzzle);
            if (!solution.empty()) {
                (*cost)++;
                return solution;
            }
        }
    }

    return vector<int>{};
}

vector<int> idfs(vector<int>& puzzle, int* cost, int* exp_nodes) {
    vector<int> solution;
    for (int limit = 0; limit <= MAX_DEPTH; limit++) {
        solution = recursive_idfs(puzzle, cost, exp_nodes, limit, vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1});
        
        if (!solution.empty()) {
            return solution;
        }
    }

    return vector<int>{};    
}

vector<vector<int>> successors(vector<int>& puzzle, vector<int> &parent) { // uses only state. works only for 8puzzle
    vector<vector<int>> result;
    int blank = 0;
    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle[i] == 0) {
            blank = i;
            break;
        }
    }

    const vector<pair<int, int>> moves = {
        {blank-3, UP},
        {blank-1, LEFT},
        {blank+1, RIGHT},
        {blank+3, DOWN}
    };

    for (const auto& pair: moves) {
        int new_blank = pair.first;
        int direction = pair.second;
        if (new_blank >= 0 && new_blank < 9 && !((blank % 3 == 0 && direction == LEFT) || (blank % 3 == 2 && direction == RIGHT))) {
            if(parent.at(new_blank) != 0) {
                swap(puzzle, new_blank, blank);
                result.push_back(puzzle);
                swap(puzzle, blank, new_blank);
            }
        }
    }

    return result;
}
