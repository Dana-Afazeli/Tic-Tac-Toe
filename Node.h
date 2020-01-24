#ifndef TIC_TAC_TOE_NODE_H
#define TIC_TAC_TOE_NODE_H

#include <vector>
#include <math.h>
#include "State.h"
using namespace std;

class Node {
public:
	Node();
	double simulate(int);
	Node &getBest();
	State &getGameState();
	Node &find(int, int);
private:
	vector<Node> subNodes;
	State gameState;
	double score;
	int played;

	double UCB(int);
	int select(int);
	double play();
	void expand();
	int random(int);

};


#endif //TIC_TAC_TOE_NODE_H
