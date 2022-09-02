//
// Created by jaehyeong on 22. 8. 22.
//
#include "TTTmcts.h"

int TTTmcts::startMCTS() {
    InitNd = new Node();
    mctsover=0;
    for(int i =0; i<Iteration; i++){
        std::cout<<"MCTS iteration: "<<i+1 <<std::endl;
        int Se = Selection();
        if(mctsover == 1){
            std::cout<<"mcts over"<<std::endl;
            break;
        }
        if(Se != 10){
            BackpropagationSe(Se);
        }
        else{
            int Ex = Expansion();
            if(mctsover == 1){
                std::cout<<"mcts over"<<std::endl;
                break;
            }
            if(Ex != 10)
                Backpropagation(Ex);
            else{
                double val = Simulation(ExpansionNd->layer);
                Backpropagation(val);
            }
        }
    }
    setFinalUCT();
    std::cout<<std::endl;
    std::cout<<std::endl<<std::endl<<"mcts is end and select: "<<InitNd->childNDs[0]->pos<<std::endl;
    return InitNd->childNDs[0]->pos;
}
void TTTmcts::initialize(){
    std::cout<<" MCTS start!!! "<<std::endl;
    std::cout<<"How many iteration will you run?? "<<std::endl;
    std::cin>>Iteration;
}
int TTTmcts::Selection() {
    Selresult = 10;
    simGameover = 0;
    SIteration = 0;
    simplace = TTT.place;
    SelectionNd = InitNd;
    while(1)
    {
        NodeCountLimit = 10-(SelectionNd->layer+TTT.iter);
        if( SelectionNd->childNDs.size() < NodeCountLimit ){
            SelectionNd->vis++;
            std::cout<<"selection node layer: "<<SelectionNd->layer << std::endl;
            if(SelectionNd->parentND!= nullptr)
                std::cout<< "parent's pos: "<<SelectionNd->parentND->pos<<std::endl;
            std::cout<<"============================="<<std::endl;
            break;
        }
        else {
            if(SelectionNd->childNDs.size()==0 && SelectionNd->full == 0)
            {
                std::cout<<"SelectionNd layer"<<SelectionNd->layer<<" can't have childNd anymore"<<std::endl;
                SelectionNd->full = 1;
                SelectionNd->vis--;
                simplace[SelectionNd->pos]=" (*) ";
                SelectionNd = SelectionNd->parentND;
                SelectionNd->parentND->vis --;
            }
            else
            {
                SelectionNd->vis ++;
                ALLfull = 0;
                for(int i=0; i<SelectionNd->childNDs.size(); i++)
                {
                    SelectionNd = SelectionNd->childNDs[i];
                    if(SelectionNd->full == 0)
                        break;
                    else
                        ALLfull++;
                }
                NodeCountLimit = 10-(SelectionNd->layer+TTT.iter);
                if(ALLfull == NodeCountLimit-1 && SelectionNd->parentND == InitNd)
                {
                    mctsover = 1;
                    break;
                }
                else if(ALLfull == NodeCountLimit)
                {
                    std::cout<<"layer "<<SelectionNd->layer<< " all full"<< std::endl;
                    mctsover = 1;
                    break;
                }
                else{
                    if((SelectionNd->layer)%2 ==0)
                        simplace[SelectionNd->pos] = " X ";
                    else
                        simplace[SelectionNd->pos] = " O ";
                    Selresult = decideWinner();
                    if(Selresult != 10)
                        return Selresult;
                }
            }
        }
    }
    return 10;
}
int TTTmcts::Expansion() {
    Placeable = findPlaceable();
    if(Placeable.size()==0){
        std::cout<<"Expansion placeable size is "<<0<<std::endl;
        mctsover=1;
    }
    else{
        srand(time(NULL));
        int chooseRand = rand()% Placeable.size();
        ExpansionNd = new Node(SelectionNd, Placeable[chooseRand]);
        if((ExpansionNd->layer)%2 ==0)
            simplace[Placeable[chooseRand]] = " X ";
        else
            simplace[Placeable[chooseRand]] = " O ";
        int result = decideWinner();
        visualPlace();
        std::cout<<"Expansion node pos: " << ExpansionNd->pos <<std::endl;
        std::cout<<"============================="<<std::endl;
        Placeable.erase(std::remove(Placeable.begin(),Placeable.end(), Placeable[chooseRand]),Placeable.end());
        return result;
    }
}
double TTTmcts::Simulation(int layer) {
    Placeable = findsimPlaceable();
    srand(time(NULL));
    while(simGameover != 1 ){
        int chooseRand = rand()%Placeable.size();
        std::cout<<"simlation select: "<<Placeable[chooseRand]<<std::endl;
        if((SIteration+layer)%2 ==1)
            simplace[Placeable[chooseRand]] = " X ";
        else
            simplace[Placeable[chooseRand]] = " O ";
        SIteration++;
        Placeable.erase(std::remove(Placeable.begin(),Placeable.end(), Placeable[chooseRand]),Placeable.end());
        winner = decideWinner();
        visualPlace();
    }
    return winner;
}
void TTTmcts::Backpropagation(double result) {
    Node* parentNd = ExpansionNd->parentND;
    Node* presentNd = ExpansionNd;
    std::cout<<"result: "<<result<<std::endl;
    std::cout<<"============================="<<std::endl<<std::endl;
    while(presentNd->parentND != nullptr) {
        presentNd->val +=result;
        if(presentNd->parentND != nullptr)
        {
            for(int i=0; i<presentNd->parentND->childNDs.size(); i++)
            {
                setUCT(presentNd->parentND->childNDs[i]);
            }
        }
        presentNd = presentNd->parentND;
    }

    presentNd = ExpansionNd;
    while(presentNd->parentND != nullptr) {
        if(presentNd->layer%2==0)
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return a->uct>b->uct;});
        else
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return b->uct>a->uct;});
        presentNd=presentNd->parentND;
    }
}
void TTTmcts::BackpropagationSe(double result) {
    Node* parentNd = SelectionNd->parentND;
    Node* presentNd = SelectionNd;
    std::cout<<"result: "<<result<<std::endl;
    std::cout<<"============================="<<std::endl<<std::endl;
    while(presentNd->parentND != nullptr) {
        presentNd->val +=result;
        if(presentNd->parentND != nullptr)
        {
            for(int i=0; i<presentNd->parentND->childNDs.size(); i++)
            {
                setUCT(presentNd->parentND->childNDs[i]);
            }
        }
        presentNd = presentNd->parentND;
    }

    presentNd = SelectionNd;
    while(presentNd->parentND != nullptr) {
        if(presentNd->layer%2==0)
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return a->uct>b->uct;});
        else
            std::sort(presentNd->parentND->childNDs.begin(), presentNd->parentND->childNDs.end(),[](Node* a, Node* b){return b->uct>a->uct;});
        presentNd=presentNd->parentND;
    }
}
void TTTmcts::setUCT(Node* nd) {
    int t = nd->parentND->vis;
    double c = sqrt(2);
    if(nd->layer%2 == 0)
        nd->uct = double(nd->val)/double(nd->vis) + c*sqrt((log(t))/(nd->vis));
    else
        nd->uct = double(nd->val)/double(nd->vis);
}
void TTTmcts::setFinalUCT() {
    for(int i =0; i<InitNd->childNDs.size(); i++)
    {
        InitNd->childNDs[i]->uct = double(InitNd->childNDs[i]->val)/double(InitNd->childNDs[i]->vis);
    }
    std::sort(InitNd->childNDs.begin(), InitNd->childNDs.end(),[](Node* a, Node* b){return a->uct>b->uct;});
}

std::vector<int>  TTTmcts::findPlaceable(){
   std::vector<int> checklist={1,2,3,4,5,6,7,8,9};
   Node* checker = SelectionNd;
   for(int i=1; i<10; i++){
       if(simplace[i] == " O " || simplace[i]== " X "){
        checklist.erase(std::remove(checklist.begin(),checklist.end(), i),checklist.end());
       }
   }
   for(int i=0; i<checker->childNDs.size(); i++){
        checklist.erase(std::remove(checklist.begin(),checklist.end(), checker->childNDs[i]->pos),checklist.end());
   }
   while(checker->pos != 0){
       checklist.erase(std::remove(checklist.begin(),checklist.end(), checker->pos),checklist.end());
       checker = checker->parentND;
   }

   return checklist;
}
std::vector<int> TTTmcts::findsimPlaceable() {
    std::vector<int> checklist={1,2,3,4,5,6,7,8,9};
    Node* checker = ExpansionNd;
    for(int i=1; i<10; i++){
        if(simplace[i] == " O " || simplace[i]== " X "){
            checklist.erase(std::remove(checklist.begin(),checklist.end(), i),checklist.end());
        }
    }
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
            if(simplace[(3*j)+i] == " X ")
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

    if(SIteration+TTT.iter+SelectionNd->layer ==9){
        std::cout<<"Draw"<<std::endl;
        simGameover = 1;
        return 0;
    }
    return 10;
}
void TTTmcts::visualPlace() {
    std::cout << std::endl;
    std::cout << simplace[1] << "  | "<< simplace[2] << " |  " << simplace[3] << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << simplace[4] << "  | "<< simplace[5] << " |  " << simplace[6] << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << simplace[7] << "  | "<< simplace[8] << " |  " << simplace[9] << std::endl;
    std::cout << std::endl;
}