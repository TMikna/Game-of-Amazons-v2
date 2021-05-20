#pragma once
#include "../../include/Player.h"
class AI :
    public Player
{
public:
    AI(Board* board, UI* ui, short teamColor) :Player(board, ui, teamColor) {};

	//Pure Virtual function
	//virtual void moveAmazon() = 0;

	//virtual void shootArrow() = 0;

	//virtual bool hasPossibleMove() = 0;
};