//
// Created by Dana on 1/23/2020.
//

#include "Node.h"

double Node::UCB(int T) {
    return score/played + expCo*sqrt(log(T)/played);
}

void Node::expand() {

}