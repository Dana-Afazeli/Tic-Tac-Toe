#include "State.h"
#include <iostream>
using namespace std;

State::State()
{
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = 0;
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			local[i][j] = 0;
		}
	}
	lastX = -1;
	lastY = -1;
	player = 1;
}

State::State(const State &state)
{
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = state.board[i][j];
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			local[i][j] = state.local[i][j];
		}
	}
	lastX = state.lastX;
	lastY = state.lastY;
	player = state.player;
}

vector<State> State::getNext()
{
	vector<State> res;
	if(lastX != -1 && lastY != -1)
	{
		if (!isFull(lastX % 3, lastY % 3))
		{
			for (int i = (lastX % 3) * 3; i < (lastX % 3) * 3 + 3; i++)
			{
				for (int j = (lastY % 3) * 3; j < (lastY % 3) * 3 + 3; j++)
				{
					if (board[i][j] == 0)
					{
						State s = *this;
						s.board[i][j] = player;
						s.player *= -1;
						s.lastX = i;
						s.lastY = j;
						res.push_back(s);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board[i][j] == 0)
					{
						State s = *this;
						s.board[i][j] = player;
						s.player *= -1;
						s.lastX = i;
						s.lastY = j;
						res.push_back(s);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == 0)
				{
					State s = *this;
					s.board[i][j] = player;
					s.player *= -1;
					s.lastX = i;
					s.lastY = j;
					res.push_back(s);
				}
			}
		}
	}
	return res;
}

int State::isFull(int x, int y)
{
	if(local[x][y] != 0)
		return 1;
	for(int i = x * 3; i < x * 3 + 3; i++)
	{
		for(int j = y * 3; j < y * 3 + 3; j++)
		{
			if(board[i][j] == 0)
				return 0;
		}
	}
	local[x][y] = -2;
	return 1;
}

int State::check()
{
	int flag = 0;
	for (int i = (lastX / 3) * 3; i < (lastX / 3) * 3 + 3; i++)
	{
		int j = (lastY / 3) * 3;
		if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
		{
			local[lastX / 3][lastY / 3] = board[i][j];
			flag = 1;
		}
	}
	if(!flag)
	{
		for (int j = (lastY / 3) * 3; j < (lastY / 3) * 3 + 3; j++)
		{
			int i = (lastX / 3) * 3;
			if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
			{
				local[lastX / 3][lastY / 3] = board[i][j];
				flag = 1;
			}
		}
	}
	if(!flag)
	{
		int i = (lastX / 3) * 3;
		int j = (lastY / 3) * 3;
		if (board[i][j] != 0 && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
		{
			local[lastX / 3][lastY / 3] = board[i][j];
			flag = 1;
		}
	}
	if(!flag)
	{
		int i = (lastX / 3) * 3 + 2;
		int j = (lastY / 3) * 3;
		if (board[i][j] != 0 && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2])
		{
			local[lastX / 3][lastY / 3] = board[i][j];
			flag = 1;
		}
	}

	//Checking Locals
	if(flag)
	{
		for (int i = 0; i < 3; i++)
		{
			int j = 0;
			if (local[i][j] != 0 && local[i][j] == local[i][j + 1] && local[i][j] == local[i][j + 2])
			{
				return local[i][j];
			}
		}
		for (int j = 0; j < 3; j++)
		{
			int i = 0;
			if (local[i][j] != 0 && local[i][j] == local[i + 1][j] && local[i][j] == local[i + 2][j])
			{
				return local[i][j];
			}
		}
		int i = 0;
		int j = 0;
		if (local[i][j] != 0 && local[i][j] == local[i + 1][j + 1] && local[i][j] == local[i + 2][j + 2])
		{
			return local[i][j];
		}
		i = 2;
		if (local[i][j] != 0 && local[i][j] == local[i - 1][j + 1] && local[i][j] == local[i - 2][j + 2])
		{
			return local[i][j];
		}
	}

	int count = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(isFull(i, j))
				count++;
		}
	}
	if(count == 9)
		return -2;
	return 0;
}

double State::eval()
{
	const double co = 1/2;

	int winner = check();
	if(winner == 0)
		return 0;
	else if(winner == 1)
	{
		int total = 0;
		double O = 0;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(local[i][j] == 1)
					total++;
				else if(local[i][j] == -1)
				{
					total++;
					O++;
				}
			}
		}
		return 1 - (O / total) * co;
	}
	else
	{
		int total = 0;
		double X = 0;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(local[i][j] == -1)
					total++;
				else if(local[i][j] == 1)
				{
					total++;
					X++;
				}
			}
		}
		return -1 + (X / total) * co;
	}
}

void State::print()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(board[i][j] == -1)
				cout << board[i][j] << " ";
			else
				cout << " " << board[i][j] << " ";
		}
		cout << endl;
	}
}

int State::getPlayer()
{
	return player;
}

int State::getLastX()
{
	return lastX;
}

int State::getLastY()
{
	return lastY;
}

void State::setPlayer(int player)
{
	this->player = player;
}

void State::setLastX(int lastX)
{
	this->lastX = lastX;
}

void State::setLastY(int)
{
	this->lastY = lastY;
}
