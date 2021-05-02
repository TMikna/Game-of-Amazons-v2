#pragma once

#include <iostream>
#include "Board.h"

class Player
{

public:

	void makeMove() {
		moveAmazon();
		shootArrow();
	}

	short getTeamColor()
	{
		return teamColor;
	}

	Player(short teamColor)
	{
		this->teamColor = teamColor;
		this->oppositeTeamColor = (teamColor * 2) % 3;
	}

	//Pure Virtual function
	virtual void moveAmazon() = 0;

	virtual void shootArrow() = 0;

	virtual bool hasPossibleMove() = 0;


protected:
	short teamColor = -1; // whites or blacks, -1 = neither
	short oppositeTeamColor = -1; // whites or blacks, -1 = neither

private:
};
