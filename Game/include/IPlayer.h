#pragma once

class IPlayer
{

public:
	//Pure Virtual function
	virtual void moveAmazon() = 0;

	virtual void shootArrow() = 0;

	virtual bool hasPossibleMove() = 0;

	virtual void makeMove() = 0;

	virtual short getTeamColor() = 0;
private:
};
