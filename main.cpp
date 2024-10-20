#include <iostream>
#include <cstring>
#include <chrono>
#include <set>
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

vector<int> swap(vector<int> puzzle, int tile_one, int tile_two) {
    vector<int> result = puzzle;

    int temp = result[tile_one];
    result[tile_one] = result[tile_two];
    result[tile_two] = temp;

    return result;
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

    if (blank - 3 >= 0) {
        if (parent->state.at(blank-3) != 0)
            result.push_back(make_node(parent, UP, swap(puzzle, blank-3, blank)));
    }

    if (blank - 1 >= 0 && blank - 1 != 2 && blank - 1 != 5) {
        if (parent->state.at(blank-1) != 0)
            result.push_back(make_node(parent, LEFT, swap(puzzle, blank-1, blank)));
    }

    if (blank + 1 <= 8 && blank + 1 != 3 && blank + 1 != 6) {
        if (parent->state.at(blank+1) != 0)
            result.push_back(make_node(parent, RIGHT, swap(puzzle, blank+1, blank)));
    }

    if (blank + 3 <= 8) {
        if (parent->state.at(blank+3) != 0)
            result.push_back(make_node(parent, DOWN, swap(puzzle, blank+3, blank)));
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
    set< vector<int> > closed;
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
                open.push_back(succ[i]);
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