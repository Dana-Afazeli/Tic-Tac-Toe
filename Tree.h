#ifndef TIC_TAC_TOE_TREE_H
#define TIC_TAC_TOE_TREE_H

#include "Node.h"

class Tree {
public:
	Node &getRoot();
	void setRoot(Node);
private:
    Node root;
};


#endif //TIC_TAC_TOE_TREE_H
