#pragma once
#include "../../include/Player.h"
#include "../../include/UI.h"

class RandomAI :
	public Player
{
public:
	RandomAI(Board* board, UI* ui, short teamColor):Player(board, ui, teamColor)
	{
		//this->board = board;
		//this->ui = ui;
	}
	//Virtual function
	virtual void moveAmazon();

	virtual void shootArrow();
	virtual bool hasPossibleMove();


private:
	//UI* ui;
	//Board* board;
	Position oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	// short** amazons; //amazons, controlled by AI;

	inline short chooseMove(short max);
};
