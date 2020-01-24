#include "Node.h"
#include <cstdlib>

#define INF 1000 * 1000 * 1000;

Node::Node()
{
	gameState = State();
	score = 0;
	played = 0;
}

double Node::UCB(int T) {
	const static double expCo = sqrt(2);
	if(played == 0)
		return INF;
    return score/played + expCo*sqrt(log((double)T)/played);
}

void Node::expand()
{
	vector<State> states = gameState.getNext();
	for (int i = 0; i < states.size(); i++)
	{
		Node n;
		n.gameState = states[i];
		n.played = 0;
		n.score = 0;
		subNodes.push_back(n);
	}
}

double Node::simulate(int T)
{
	double s;
	if(subNodes.empty())
	{
		if(gameState.check() != 0)
		{
			played++;
			score = gameState.eval();
			return score;
		}
		else if(played == 0)
		{
			s = play();
			played++;
			score += gameState.getPlayer() * s;
			return score;
		}
		else
		{
			expand();
		}
	}

	int i = select(T);
	s = subNodes[i].simulate(T);
	played++;
	score += gameState.getPlayer() * s;
	return s;
}

Node& Node::getBest()
{
	int max = -INF;
	int maxi = -1;

	for(int i = 0; i < subNodes.size(); i++)
	{
		if(subNodes[i].gameState.check() == 1)
			return subNodes[i];

		if(subNodes[i].played > max)
		{
			maxi = i;
			max = subNodes[i].played;
		}
	}

	return subNodes[maxi];
}

State& Node::getGameState()
{
	return gameState;
}

Node& Node::find(int x, int y)
{
	Node n;
	for(int i = 0; i < subNodes.size(); i++)
	{
		if(subNodes[i].gameState.getLastX() == x && subNodes[i].gameState.getLastY() == y)
			return subNodes[i];
	}
	return n;
}

int Node::select(int T)
{
	static int call = 0;
	call++;
	double max = -INF;
	int maxi = -1;
	for(int i = 0; i < subNodes.size(); i++)
	{
		double ucb = subNodes[i].UCB(T);
		if(ucb > max)
		{
			max = ucb;
			maxi = i;
		}
	}
	return maxi;
}

double Node::play()
{
	if(gameState.check() != 0)
		return gameState.eval();

	vector<State> states = gameState.getNext();
	if(states.empty())
	{
		gameState.print();
		gameState.check();
		gameState.getNext();
		return 0;
	}
	int i = random(states.size());
	Node n;
	n.gameState = states[i];
	return n.play();
}

int Node::random(int n)
{
	return rand() % n;
}