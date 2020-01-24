#ifndef TIC_TAC_TOE_STATE_H
#define TIC_TAC_TOE_STATE_H

#include <vector>
using namespace std;

class State {
public:
	State();
	State(const State &state);
    vector<State> getNext();
	int check();
	double eval();
	void print();
	int getPlayer();
	void setPlayer(int);
	int getLastX();
	void setLastX(int);
	int getLastY();
	void setLastY(int);
private:
	int board[9][9];
	int local[3][3];
	int lastX;
	int lastY;
	int player;

	int isFull(int, int);
};


#endif //TIC_TAC_TOE_STATE_H
