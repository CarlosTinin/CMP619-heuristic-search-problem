#include <iostream>
#include <cstring>
#include <chrono>
#include <unordered_set>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

struct Entry {
    string algorithm;
    vector< vector<int> > puzzles;
};

enum ACTIONS {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    INITIAL
};

struct Node {
    vector<int> state;
    Node* parent;
    enum ACTIONS action;
    int path_cost;
};

struct CompareNode {
    bool operator() (Node const& n1, Node const& n2) {
        return n1.path_cost > n2.path_cost;
    }
};

struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        string hash;
        for (int i : v) {
            hash += to_string(i);
        }
        return std::hash<string>()(hash);
    }
};

Node make_root_node(vector<int> state) {
    Node node;
    node.state = state;
    node.parent = NULL;
    node.action = INITIAL;
    node.path_cost = 0;

    return node;
}

Node make_node(Node* parent, ACTIONS action, vector<int> state) {
    Node node;
    node.state = state;
    node.parent = parent;
    node.action = action;
    node.path_cost = parent->path_cost + 1;

    return node;
}

void swap(vector<int> first_position, vector<int> second_position) {

    vector<int> temp = first_position;
    first_position = second_position;
    second_position = temp;
}

vector<Node> successors(vector<int> puzzle, Node* parent) { // works for 8puzzle
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
            swap(puzzle[new_blank], puzzle[blank]);
            result.push_back(make_node(parent, UP, puzzle));
            swap(puzzle[blank], puzzle[new_blank]);
        }
    }

    return result;
}

bool is_goal(vector<int> puzzle) {
    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle.at(i) != i) {
            return false;
        }
    }

    return true;
}

void printState(vector<int> vect);

void astar() {
    printf("TODO: ASTAR");
}

Node bfs(vector<int> puzzle, int* exp_nodes) {
    if (is_goal(puzzle)) {
        return (Node) {};
    }
    deque<Node> open;
    open.push_back(make_root_node(puzzle));
    unordered_set< vector<int>, VectorHash > closed;
    closed.insert(puzzle);

    while (!open.empty()) {
        Node n = open.front();
        open.pop_front();
        vector<Node> succ = successors(n.state, &n);
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

void gbfs() {
    priority_queue <Node, vector<Node>, CompareNode > open; // min-heap
    printf("TODO: GBFS");
}

void idastar() {
    printf("TODO: IDASTAR");
}

void idfs() {
    printf("TODO: IDFS");
}

Entry parseArguments(int count, char* argv[]);

void printEntry(Entry entry);

int main(int argc, char* argv[]) {
    if (argc < 11) {
        cout << "Invalid entry size.";
        return 0;
    }
    Entry entry = parseArguments(argc, argv);

    if (entry.algorithm == "-astar") {
        astar();
    } else if (entry.algorithm == "-bfs") {
        for (int i = 0; i < entry.puzzles.size(); i++ ) {
            int expanded_nodes = 0;

            auto init = high_resolution_clock::now();
            Node result = bfs(entry.puzzles.at(i), &expanded_nodes);
            auto finish = high_resolution_clock::now();

            duration<double> elapsed_time = finish - init;
            cout << expanded_nodes << ",";
            cout << result.path_cost << ",";
            cout << elapsed_time.count() << ",";
            cout << "0,\n";
        }
    } else if (entry.algorithm == "-idastar") {
        idastar();
    } else if (entry.algorithm == "-idfs") {
        idfs();
    } else {
        gbfs();
    }

    //printEntry(entry);

    return 0;
}

Entry parseArguments(int count, char* argv[]) {
    Entry entry;

    entry.algorithm = argv[1];
    vector<int> puzzle;

    for (int i = 0; i < count - 2; i++) {
        if (!strchr(argv[i+2], ',')) {
            puzzle.push_back(atoi(argv[i+2]));
        } else {
            puzzle.push_back(atoi(argv[i+2]));
            entry.puzzles.push_back(puzzle);
            puzzle.clear();
        }
    }

    if (!puzzle.empty())
        entry.puzzles.push_back(puzzle);

    return entry;
}

void printEntry(Entry entry) {
    cout << "Alg: " << entry.algorithm << "\n";
    for (int i = 0; i < entry.puzzles.size(); i++) {
        printf("Entry: ");
        for (int j = 0; j < entry.puzzles.at(i).size(); j++) {
            cout << entry.puzzles.at(i).at(j) << " ";
        }
        printf("\n");
    }
}

void printState(vector<int> vect) {
    cout << "[";
    for (int i =0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "];";
}


// printState(n.state);

// cout << " successors: ";
// for (int i = 0; i < succ.size(); i++){
//     printState(succ[i].state);
// }

// cout << "\n";