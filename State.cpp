#include "State.h"

vector<State> State::getNext()
{
	vector<State> res;

	if (local[lastX / 3][lastY / 3] == 0)
	{
		for (int i = (lastX / 3) * 3; i < (lastX / 3) * 3 + 3; i++)
		{
			for (int j = (lastX / 3) * 3; j < (lastX / 3) * 3 + 3; j++)
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
	return res;
}

int State::check()
{
	int flag = 0;
	for (int i = (lastX / 3) * 3; i < (lastX / 3) * 3 + 3; i++)
	{
		int j = (lastX / 3) * 3;
		if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
		{
			local[lastX / 3][lastY / 3] = board[i][j];
			flag = 1;
		}
	}
	if(!flag)
	{
		for (int j = (lastX / 3) * 3; j < (lastX / 3) * 3 + 3; j++)
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
		int j = (lastX / 3) * 3;
		if (board[i][j] != 0 && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
		{
			local[lastX / 3][lastY / 3] = board[i][j];
			flag = 1;
		}
	}
	if(!flag)
	{
		int i = (lastX / 3) * 3 + 2;
		int j = (lastX / 3) * 3;
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

int State::getPlayer()
{
	return player;
}