#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tree.h"
#include "Node.h"
#include "State.h"

int main() {
	srand(time(NULL));
    int x, y;
    Tree tree;
    tree.getRoot().getGameState().setLastX(-1);
    tree.getRoot().getGameState().setLastY(-1);

    while(!tree.getRoot().getGameState().check())
	{
		for (int i = 1; i < 10000; ++i)
		{
			tree.getRoot().simulate(i);
		}
		Node n = tree.getRoot().getBest();
		cout << n.getGameState().getLastX() + 1 << " " << n.getGameState().getLastY() + 1 << endl;
		cin >> x >> y;
		x--;
		y--;
		Node next = n.find(x, y);
		tree.setRoot(next);
	}
    return 0;
}