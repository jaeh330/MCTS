//
// Created by jaehyeong on 22. 8. 22.
//

#ifndef RAISIM_MCTS_H
#define RAISIM_MCTS_H
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "TicTaeToe.h"

struct Node
{
// first Node declaration
    Node() : val(0), vis(0), uct(0), parentND((nullptr)), childNDs(), layer(1), pos(0) {}
// After first Node declaration
    Node(struct Node* paND, int place) : val(0), vis(0), uct(0), parentND(paND), childNDs(), layer(paND->layer+1), pos(place) { paND->childNDs.push_back(this);}
    
    int val;
    int vis;
    int pos;
    int layer;
    double uct;
    struct Node* parentND;
    std::vector<struct Node*> childNDs;
};

class TTTmcts {
public:

    TTTmcts()
    {
        initialize();
    }


    int startMCTS();
    TicTaeToe TTT;


private:
    void initialize();
    void setUCT(Node* nd);
    std::vector<int> findPlaceable();

    //    mcts stage
    void Selection();
    void Expansion();
    double Simulation(int layer);
    void Backpropagation(double result);
    double decideWinner();


    Node* InitNd;
    Node* SelectionNd;
    Node* ExpansionNd;

    int NodeCountLimit;
    int SIteration;
    int Iteration;
    int SimulationResult;
    int simGameover;
    std::vector<int> Placeable;
    std::vector<std::string> simplace;



};


#endif //RAISIM_MCTS_H
