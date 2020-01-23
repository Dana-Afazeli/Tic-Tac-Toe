#include "Node.h"
#include <random>
#include <ctime>

#define INF 1000 * 1000 * 1000;

double Node::UCB(int T) {
	if(played == 0)
		return INF;
    return score/played + expCo*sqrt(log(T)/played);
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

Node Node::getBest()
{
	int max = -INF;
	int maxi = -1;

	for(int i = 0; i < subNodes.size(); i++)
	{
		if(subNodes[i].played > max)
		{
			maxi = i;
			max = subNodes[i].played;
		}
	}

	return subNodes[maxi];
}

int Node::select(int T)
{
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
	int i = random(states.size());
	Node n;
	n.gameState = states[i];
	return n.play();
}

int Node::random(int n)
{
	srand(time(nullptr));
	return rand() % n;
}