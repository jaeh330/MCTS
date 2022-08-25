//
// Created by jaehyeong on 22. 7. 6.
//
#ifndef MCTS_TICTAETOE_H
#define MCTS_TICTAETOE_H

#include <iostream>
#include <vector>
#include <string>

class TicTaeToe {
public:
    TicTaeToe()
    {
        std::cout << "Tic Tae Toe game!!" << std::endl;
        std::cout << std::endl;
        std::cout << place[1] << "  | "<< place[2] << " |  " << place[3] << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << place[4] << "  | "<< place[5] << " |  " << place[6] << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << place[7] << "  | "<< place[8] << " |  " << place[9] << std::endl;
        std::cout << std::endl;
        iter=0;
    }


    void startGame();
    std::vector<std::string> place = {"0","(1)","(2)","(3)","(4)","(5)","(6)","(7)","(8)","(9)"};
    int iter;
    int Gameover;
    int ai;

private:
    int breakpoint;
    std::vector<int> exist ={0,0,0,0,0,0,0,0,0,0};
    int input;
    std::string turn;

    void decidewinner();

};




#endif //MCTS_TICTAETOE_H
