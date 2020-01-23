//
// Created by Dana on 1/23/2020.
//

#ifndef TIC_TAC_TOE_NODE_H
#define TIC_TAC_TOE_NODE_H

#include <vector>
#include <math.h>
using namespace std;

class Node {
public:
    double UCB(int);
    void expand();
private:
    vector<Node> subNodes;
    double score;
    int played;
    const double expCo = sqrt(2);

};


#endif //TIC_TAC_TOE_NODE_H
