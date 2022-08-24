//
// Created by jaehyeong on 22. 8. 22.
//
#include "mcts.h"

// MCTS iteration setting and initialize
void mcts::initialize(){
    std::cout<<" MCTS start!!! "<<std::endl;
    std::cout<<"How many iteration will you run?? "<<std::endl;
    std::cin>>Iteration;
    InitNd = new Node();
}

void mcts::Selection() {
    SelectionNd = InitNd;
    while(1)
    {
        if( InitNd->childNDs.size() < NodeCountLimit ){
            break;
        }
        else {
            SelectionNd = SelectionNd->childNDs[0];
        }
    }
}

void mcts::Expansion() {
    ExpansionNd = new Node(SelectionNd);
}

void mcts::Simulation() {
    SIteration = 0;
    /* Simulation code
     * you should put your platform simulation code
     */
    SIteration = 0;
}

void mcts::Backpropagation() {
    Node* parentNd = ExpansionNd->parentND;
    Node* presentNd = ExpansionNd;
    for(int i=0; i<parentNd->childNDs.size(); i++){
        parentNd->childNDs[i]->val +=1;
        parentNd->childNDs[i]->vis +=1;
        setUCT(parentNd->childNDs[i]);
        if(i == parentNd->childNDs.size()-1){
            if(parentNd->parentND == nullptr)
                break;
            else {
                parentNd = parentNd->parentND;
            }
        }
    }

    while(presentNd->parentND != nullptr) {
        for(int i=0; i < presentNd->parentND->childNDs.size(); i++){
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return a->uct>b->uct;});
        }
    }
}

//UCT setting
void mcts::setUCT(Node* nd) {
    int t = nd->parentND->vis+1;
    double c = sqrt(2); // exploration parameter - you should find this value experimentally.
    nd->uct = double(nd->val)/double(nd->vis) + c*sqrt((log(t))/(nd->vis));
}

