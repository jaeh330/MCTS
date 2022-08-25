//
// Created by jaehyeong on 22. 8. 24.
//

#include "TicTaeToe.h"
#include "TTTmcts.h"

int main() {
    TTTmcts ai;
    while(ai.TTT.Gameover !=1){
        ai.TTT.startGame();
        int input = ai.startMCTS();
        std::cout<<input<<std::endl;
    }
    return 0;
}
