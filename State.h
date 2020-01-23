//
// Created by Dana on 1/23/2020.
//

#ifndef TIC_TAC_TOE_STATE_H
#define TIC_TAC_TOE_STATE_H

#include <vector>
using namespace std;

class State {
public:
    vector<State> get();
private:
    int board[9][9];
    int local[3][3];
    int lastX;
    int lastY;
    int player;
};


#endif //TIC_TAC_TOE_STATE_H
