//
// Created by jaehyeong on 22. 8. 22.
//
#include "TTTmcts.h"

// MCTS iteration setting and initialize
int TTTmcts::startMCTS() {
    InitNd = new Node();
    simplace = TTT.place;
    for(int iter =0; iter<Iteration; iter++){
        Selection();
        Expansion();
        double val = Simulation(ExpansionNd->layer);
        Backpropagation(val);
    }

    return InitNd->childNDs[0]->pos;
}



void TTTmcts::initialize(){
    std::cout<<" MCTS start!!! "<<std::endl;
    std::cout<<"How many iteration will you run?? "<<std::endl;
    std::cin>>Iteration;
}

void TTTmcts::Selection() {
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

void TTTmcts::Expansion() {
    Placeable = findPlaceable();
    srand(time(NULL));
    int chooseRand = rand()% Placeable.size();
    ExpansionNd = new Node(SelectionNd, Placeable[chooseRand]);
    if((ExpansionNd->layer)%2 ==0)
        simplace[Placeable[chooseRand]] = " X ";
    else
        simplace[Placeable[chooseRand]] = " O ";
    Placeable.erase(std::remove(Placeable.begin(),Placeable.end(), Placeable[chooseRand]),Placeable.end());
}

double TTTmcts::Simulation(int layer) {
    SIteration = 0;
    simGameover = 0;
    srand(time(NULL));
    while(simGameover != 1){
        int chooseRand = rand()%Placeable.size();
        if((SIteration+layer)%2 ==0)
            simplace[Placeable[chooseRand]] = " X ";
        else
            simplace[Placeable[chooseRand]] = " O ";
        SIteration++;
        return decideWinner();
    }
}

void TTTmcts::Backpropagation(double result) {
    Node* parentNd = ExpansionNd->parentND;
    Node* presentNd = ExpansionNd;
    while(presentNd->parentND != nullptr) {
        if(presentNd->layer%2 ==0)
            presentNd->val +=result;
        else
            presentNd->val -=result;
        presentNd = presentNd->parentND;
    }

    for(int i=0; i<parentNd->childNDs.size(); i++){
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
    presentNd = ExpansionNd;
    while(presentNd->parentND != nullptr) {
        for(int i=0; i < presentNd->parentND->childNDs.size(); i++){
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return a->uct>b->uct;});
        }
    }
}

//UCT setting
void TTTmcts::setUCT(Node* nd) {
    int t = nd->parentND->vis+1;
    double c = sqrt(2); // exploration parameter - you should find this value experimentally.
    nd->uct = double(nd->val)/double(nd->vis) + c*sqrt((log(t))/(nd->vis));
}

std::vector<int>  TTTmcts::findPlaceable(){
   std::vector<int> checklist={1,2,3,4,5,6,7,8,9};
   Node* checker = SelectionNd;
   //real place
   for(int i=1; i<10; i++){
       if(simplace[i] == " O " || simplace[i]== " X "){
        checklist.erase(std::remove(checklist.begin(),checklist.end(), i),checklist.end());
       }
   }
    //neighbor place
    for(int i=0; i<checker->childNDs.size(); i++){
        checklist.erase(std::remove(checklist.begin(),checklist.end(), checker->childNDs[i]->pos),checklist.end());
    }
   //parent place
   while(checker->pos != 0){
       checklist.erase(std::remove(checklist.begin(),checklist.end(), checker->pos),checklist.end());
       checker = checker->parentND;
   }

   return checklist;
}

double TTTmcts::decideWinner(){
    for(int i=0; i<3; i++)
    {
        int j=1;
        if( simplace[(3*i)+j] == simplace[(3*i)+j+1] && simplace[(3*i)+j+1] == simplace[(3*i)+j+2] ){
            simGameover=1;
            if(simplace[(3*i)+j+1] == " X ")
                return 1;
            else
                return -1;
        }
    }
    for(int i=1; i<4; i++)
    {
        int j=0;
        if( simplace[(3*j)+i] == simplace[(3*(j+1))+i] && simplace[(3*(j+1))+i] == simplace[(3*(j+2))+i] ){
            simGameover=1;
            if(simplace[(3*i)+j+1] == " X ")
                return 1;
            else
                return -1;
        }
    }
    if( (simplace[1] == simplace[5] && simplace[5]== simplace[9]) ||  (simplace[3] == simplace[5] && simplace[5]==simplace[7])){
        simGameover=1;
        if(simplace[5] == " X ")
            return 1;
        else
            return -1;
    }

    if(SIteration ==9){
        simGameover = 1;
        return 0;
    }
}