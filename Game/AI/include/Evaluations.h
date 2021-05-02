#pragma once
#include "../../include/Board.h"

// template/base class for all evaluations
class Evaluation
{
public:
	Evaluation() {}

	//Pure Virtual function
	//virtual float Evaluate(Board* board, short teamColor) = 0;
	virtual float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor) = 0;


protected:
	//short teamColor = -1;			// whites or blacks, -1 = neither
	//short oppositeTeamColor = -1;	// whites or blacks, -1 = neither
	//Board* board;					// board state
private:
};


class PossibleMovesEvaluation :
	public Evaluation
{
public:
	float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor);

}; 

class DirectionsMovesEvaluation :
	public Evaluation
{
public:
	float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor);

};

