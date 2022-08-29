//
// Created by jaehyeong on 22. 8. 24.
//

#include "TicTaeToe.h"
#include "TTTmcts.h"

int main() {
    TTTmcts ai;
    while(1){
        ai.TTT.startGame();
        if(ai.TTT.Gameover == 1)
            break;
        int input = ai.startMCTS();
        ai.TTT.AIstartGame(input);
        if(ai.TTT.Gameover == 1)
            break;
    }
    return 0;
}
