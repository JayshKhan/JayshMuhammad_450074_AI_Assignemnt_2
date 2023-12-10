//
// Created by Jaysh Khan on 12/10/23.
//

#ifndef INC_8_PUZZLE_PROBLEM_USING_A_ALGORITHM_FINAL_H
#define INC_8_PUZZLE_PROBLEM_USING_A_ALGORITHM_FINAL_H

#endif //INC_8_PUZZLE_PROBLEM_USING_A_ALGORITHM_FINAL_H

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>


using namespace std;

enum Heuristic {
    MisplacedTiles, ManhattanDistance
};

// Structure to represent a puzzle state
struct State {
    vector<vector<int>> puzzleBoard;
    int gCost; // Cost to reach this state
    int hCost; // Heuristic cost of this state
    int fCost; // Total cost of this state
    Heuristic heuristic; // Heuristic function used to calculate hCost

    State *parentState = nullptr; // Pointer to the parent state

    void createState(int g_cost, State *parent_state = nullptr, Heuristic h = ManhattanDistance ) {
        this->gCost = g_cost;
        this->heuristic = h;
        this->parentState = parent_state;
        this->hCost = h == ManhattanDistance ? getManhattanDistance() : getMisplacedTiles();
        this->fCost = gCost + hCost;
    }

    bool operator==(const State &other) const {
        return puzzleBoard == other.puzzleBoard;
    }

    bool operator<(const State &other) const {
        return fCost > other.fCost; // Priority queue uses the greater than operator
    }

    // Hash function for unordered_set
    struct HashFunction {
        size_t operator()(const State &state) const {
            size_t hash = 0;
            for (int i = 0; i < state.puzzleBoard.size(); ++i) {
                for (int j = 0; j < state.puzzleBoard[i].size(); ++j) {
                    hash += state.puzzleBoard[i][j] * (i * state.puzzleBoard.size() + j);
                }
            }
            return hash;
        }
    };



    struct CompareGS //greedy search comparator for priority queue
    {
        bool operator()(const State *lhs, const State *rhs) const {
            return lhs->hCost > rhs->hCost;
        }
    };
    struct CompareAStar //A* search comparator for priority queue
    {
        bool operator()(const State *lhs, const State *rhs) const {
            return lhs->fCost > rhs->fCost;
        }
    };

    int  getMisplacedTiles(){
        int h_cost = 0;
        for (int i = 0; i < puzzleBoard.size(); i++) {
            for (int j = 0; j < puzzleBoard[i].size(); j++) {
                if (puzzleBoard[i][j] != 0 && puzzleBoard[i][j] != i * puzzleBoard.size() + j + 1) {
                    h_cost++;
                }
            }
        }
        return h_cost;

    }
    int getManhattanDistance(){
        int h_cost = 0;
        for (int i = 0; i < puzzleBoard.size(); i++) {
            for (int j = 0; j < puzzleBoard[i].size(); j++) {
                if (puzzleBoard[i][j] != 0) {
                    int x = (puzzleBoard[i][j] - 1) / 3;
                    int y = (puzzleBoard[i][j] - 1) % 3;
                    h_cost += abs(x - i) + abs(y - j);
                }
            }
        }
        return h_cost;
    }


    vector<State *> getSuccessors() {
        vector<State *> successors;
        int emptyRow = -1;
        int emptyCol = -1;
        for (int i = 0; i < puzzleBoard.size(); ++i) {
            for (int j = 0; j < puzzleBoard[i].size(); ++j) {
                if (puzzleBoard[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                    break;
                }
            }
        }
        if (emptyRow > 0) {
            vector<vector<int>> newState = puzzleBoard;
            swap(newState[emptyRow][emptyCol], newState[emptyRow - 1][emptyCol]);
            auto *successor = new State();
            successor->puzzleBoard = newState;
            successor->createState(gCost + 1, this,this->heuristic);
            successors.push_back(successor);
        }
        if (emptyRow < puzzleBoard.size() - 1) {
            vector<vector<int>> newState = puzzleBoard;
            swap(newState[emptyRow][emptyCol], newState[emptyRow + 1][emptyCol]);
            auto *successor = new State();
            successor->puzzleBoard = newState;
            successor->createState(gCost + 1, this,this->heuristic);
            successors.push_back(successor);
        }
        if (emptyCol > 0) {
            vector<vector<int>> newState = puzzleBoard;
            swap(newState[emptyRow][emptyCol], newState[emptyRow][emptyCol - 1]);
            auto *successor = new State();
            successor->puzzleBoard = newState;
            successor->createState(gCost + 1, this,this->heuristic);
            successors.push_back(successor);
        }
        if (emptyCol < puzzleBoard.size() - 1) {
            vector<vector<int>> newState = puzzleBoard;
            swap(newState[emptyRow][emptyCol], newState[emptyRow][emptyCol + 1]);
            auto *successor = new State();
            successor->puzzleBoard = newState;
            successor->createState(gCost + 1, this,this->heuristic);
            successors.push_back(successor);
        }
        return successors;
    }
};

struct Solution {
    int nodesExpanded;
    vector<State *> path;

    void printSolution() {
        cout << "Nodes Expanded: " << nodesExpanded << endl;
        cout << "Path: " << endl;
        for (auto &i: path) {
            for (auto &j: i->puzzleBoard) {
                for (int k: j) {
                    cout << k << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

};
