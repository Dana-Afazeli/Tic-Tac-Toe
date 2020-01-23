//
// Created by Dana on 1/23/2020.
//

#include "State.h"

vector<State> State::get() {
    vector<State> res;

    if(local[lastX / 3][lastY / 3] == 0)
    {
        for(int i = (lastX / 3) * 3; i < (lastX / 3) * 3 + 3; i++)
        {
            for(int j = (lastX / 3) * 3; j < (lastX / 3) * 3 + 3; j++)
            {
                if(board[i][j] == 0)
                {
                    State s = *this;
                    s.board[i][j] = player;


                }
            }
        }
    }
}