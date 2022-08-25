//
// Created by jaehyeong on 22. 7. 6.
//

#include "TicTaeToe.h"

void TicTaeToe::startGame(){
    if(iter%2 ==1){
        turn = " X ";
    }
    else{
        turn= " O ";
    }

    std::cout << "It is a" << turn << "turn !!" << std::endl;
    std::cout << "Where do you want to put Go??" << std::endl;
    std::cin >> input;
    switch (input)
    {
        case 1:
            if(exist[1]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[1] = turn;
            exist[1]=1;
            iter++;
            break;
        case 2:
            if(exist[2]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[2] = turn;
            exist[2]=1;
            iter++;
            break;
        case 3:
            if(exist[3]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[3] = turn;
            exist[3]=1;
            iter++;
            break;
        case 4:
            if(exist[4]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[4] = turn;
            exist[4]=1;
            iter++;
            break;
        case 5:
            if(exist[5]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[5] = turn;
            exist[5]=1;
            iter++;
            break;
        case 6:
            if(exist[6]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[6] = turn;
            exist[6]=1;
            iter++;
            break;
        case 7:
            if(exist[7]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                iter--;
                break;
            }
            place[7] = turn;
            exist[7]=1;
            break;
        case 8:
            if(exist[8]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[8] = turn;
            exist[8]=1;
            iter++;
            break;
        case 9:
            if(exist[9]==1){
                std::cout << "You cannot place here! -_-";
                std::cout << std::endl;
                break;
            }
            place[9] = turn;
            exist[9]=1;
            iter++;
            break;
        default:
            std::cout << "You cannot place here! -_-";
            std::cout << std::endl;
            break;
    }

    std::cout << std::endl;
    std::cout << place[1] << "  | "<< place[2] << " |  " << place[3] << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << place[4] << "  | "<< place[5] << " |  " << place[6] << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << place[7] << "  | "<< place[8] << " |  " << place[9] << std::endl;
    std::cout << std::endl;

    decidewinner();
}

void TicTaeToe::decidewinner() {
    for(int i=0; i<3; i++)
    {
        int j=1;
        if( place[(3*i)+j] == place[(3*i)+j+1] && place[(3*i)+j+1] == place[(3*i)+j+2] ){
            std::cout << place[(3*i)+j+1] << "is winner!!" << std::endl;
            Gameover =1;
        }
    }
    for(int i=1; i<4; i++)
    {
        int j=0;
        if( place[(3*j)+i] == place[(3*(j+1))+i] && place[(3*(j+1))+i] == place[(3*(j+2))+i] ){
            std::cout << place[(3*(j+1))+i] << "is winner!!" << std::endl;
            Gameover =1;
        }
    }
    if( (place[1] == place[5] && place[5]==place[9]) ||  (place[3] == place[5] && place[5]==place[7])){
        std::cout << place[5] << "is winner!!" << std::endl;
        Gameover =1;
    }

    if(iter ==9){
        std::cout << "Draw" << std::endl;
        Gameover = 1;
    }
}