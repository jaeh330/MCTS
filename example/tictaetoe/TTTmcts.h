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
    Node() : val(0), vis(0), uct(0), parentND((nullptr)), childNDs(), layer(1), pos(0), full(0) {}
    Node(struct Node* paND, int place) : val(0), vis(1), uct(0), parentND(paND), childNDs(), layer(paND->layer+1), pos(place), full(0) { paND->childNDs.push_back(this);}
    
    int val;
    int vis;
    int pos;
    int layer;
    int full;
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
    void setFinalUCT();
    std::vector<int> findPlaceable();
    std::vector<int> findsimPlaceable();

    int Selection();
    int Expansion();
    double Simulation(int layer);
    void Backpropagation(double result);
    void BackpropagationSe(double result);
    double decideWinner();
    void visualPlace();

    Node* InitNd;
    Node* SelectionNd;
    Node* ExpansionNd;

    int NodeCountLimit;
    int SIteration;
    int Iteration;
    int Selresult;
    int ALLfull;
    int SimulationResult;
    int simGameover;
    int mctsover;
    int winner;
    std::vector<int> Placeable;
    std::vector<std::string> simplace;
};


#endif //RAISIM_MCTS_H
