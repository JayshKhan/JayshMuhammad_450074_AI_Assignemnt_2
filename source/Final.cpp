//
// Created by Jaysh Khan on 12/10/23.
//

#include "../Header/Final.h"

// Function Definitions
Solution* GS(State*,State*),*AStar(State*,State*);
vector<vector<int>> inputPuzzle(vector<vector<int>>*);
void printState(State*);


Heuristic inputHeuristic();

int main()
{
    auto* startState = new State();
    auto* goalState = new State();
    goalState->puzzleBoard = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    inputPuzzle(&startState->puzzleBoard);

    Heuristic heuristic=inputHeuristic();

    startState->createState(0, nullptr, heuristic);

    printState(startState);

    //Greedy Search
    auto* solution = GS(startState, goalState);
    if (solution != nullptr) {
        cout << "Greedy Search Solution Path:" << endl;
        solution->printSolution();
    } else {
        cout << "No solution found!" << endl;
    }

    //A*
    solution = AStar(startState, goalState);
    if (solution != nullptr) {
        cout << "A* Solution Path:" << endl;
        solution->printSolution();
    } else {
        cout << "No solution found!" << endl;
    }

    delete startState;
    delete goalState;
    delete solution;

    return 0;
}

Heuristic inputHeuristic() {
    cout << "Heuristic Function: " << endl;
    cout << "1. Number of misplaced tiles" << endl;
    cout << "2. Manhattan Distance" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            return Heuristic::MisplacedTiles;
        case 2:
            return Heuristic::ManhattanDistance;
        default:
            cout << "Invalid choice. Setting heuristic to 1." << endl;
            return Heuristic::MisplacedTiles;

    }

}

vector<vector<int>> inputPuzzle(vector<vector<int>> *puzzle) {
    int num;
    vector<int> row;
    for (int i = 0; i < 3; i++) {
        cout << "Enter row " << i + 1 << " of the puzzle: ";
        for (int j = 0; j < 3; j++) {
            cin >> num;
            row.push_back(num);
        }
        puzzle->push_back(row);
        row.clear();
    }
    return *puzzle;
}

void printState(State* state) {
    cout << "Current State:" << endl;
    for (const auto& row : state->puzzleBoard) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}


Solution* GS(State* startState, State* goalState)
{
    auto* solution = new Solution();
    priority_queue<State*, vector<State*>, State::CompareGS> frontier;
    unordered_set<State*> explored;
    frontier.push(startState);

    char animation[4] = {'-', '\\', '|', '/'};
    int animationIndex = 0;

    while (!frontier.empty()) {
        State* currentState = frontier.top();
        frontier.pop();
        explored.insert(currentState);

        if (currentState->puzzleBoard == goalState->puzzleBoard) {
            solution->nodesExpanded = (int)explored.size();
            while (currentState != nullptr) {
                solution->path.push_back(currentState);
                currentState = currentState->parentState;
            }
            return solution;
        }
        vector<State*> successors = currentState->getSuccessors();
        for (State* successor : successors) {
            if (explored.find(successor) == explored.end()) {
                frontier.push(successor);
            }
        }
        cout << "\rSearching " << animation[animationIndex % 4] << flush;
        animationIndex++;
//

    }
    return nullptr;
}

Solution* AStar(State* startState, State* goalState)
{
    auto* solution = new Solution();
    priority_queue<State*, vector<State*>, State::CompareAStar> frontier;
    unordered_set<State*> explored;
    frontier.push(startState);

    char animation[4] = {'-', '\\', '|', '/'};
    int animationIndex = 0;


    while (!frontier.empty()) {
        State* currentState = frontier.top();
        frontier.pop();
        explored.insert(currentState);
        if (currentState->puzzleBoard == goalState->puzzleBoard) {
            solution->nodesExpanded = (int)explored.size();
            while (currentState != nullptr) {
                solution->path.push_back(currentState);
                currentState = currentState->parentState;
            }
            return solution;
        }
        vector<State*> successors = currentState->getSuccessors();
        for (State* successor : successors) {
            if (explored.find(successor) == explored.end()) {
                frontier.push(successor);
            }
        }
        cout << "\rSearching " << animation[animationIndex % 4] << flush;
        animationIndex++;

    }
    return nullptr;
}