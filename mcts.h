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

// Please add more information about your platform node
struct Node
{
// first Node declaration
    Node() : val(0), vis(0), uct(0), parentND((nullptr)), childNDs(), layer(1) {}
// After first Node declaration
    Node(struct Node* paND) : val(0), vis(0), uct(0), parentND(paND), childNDs(), layer(paND->layer+1) { paND->childNDs.push_back(this);}
    
    int val;
    int vis;
    int pos1;
    int pos2;
    int layer;
    double uct;
    struct Node* parentND;
    std::vector<struct Node*> childNDs;
};

class mcts {
public:
    mcts(){
        initialize();
        for(int iter =0; iter<Iteration; iter++){
            Selection();
            Expansion();
            Simulation();
            Backpropagation();
        }
    }

    void initialize();
    void setUCT(Node* nd);

    //    mcts stage
    void Selection();
    void Expansion();
    void Simulation();
    void Backpropagation();


private:

    Node* InitNd;
    Node* SelectionNd;
    Node* ExpansionNd;
    int NodeCountLimit;
    int SIteration;
    int Iteration;
    int SimulationResult;

};


#endif //RAISIM_MCTS_H
