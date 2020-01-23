#ifndef TIC_TAC_TOE_NODE_H
#define TIC_TAC_TOE_NODE_H

#include <vector>
#include <math.h>
#include "State.h"
using namespace std;

class Node {
public:
	double simulate(int);
	Node getBest();
private:
	vector<Node> subNodes;
	State gameState;
	double score;
	int played;
	const double expCo = sqrt(2);

	double UCB(int);
	int select(int);
	double play();
	void expand();
	int random(int);

};


#endif //TIC_TAC_TOE_NODE_H
