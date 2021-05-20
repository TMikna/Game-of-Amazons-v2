#pragma once
#include "../../include/Player.h"
#include "../../include/UI.h"
#include "Evaluations.h"
#include "AI.h"


class AlfaBetaAI_ss :
    public AI
{

public:
	AlfaBetaAI_ss(Board* board, Evaluation* evaluation, UI* ui, short teamColor, short maxDepth = c::MAX_SEARCH_DEPTH):AI(board, ui, teamColor)
	{
		this->evaluation = evaluation;
		this->maximumSearchDepth = maxDepth;
	}
	//Virtual function
	virtual void moveAmazon();
	virtual void shootArrow();
	virtual bool hasPossibleMove();


private:
	Position oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	Evaluation* evaluation;
	short MAX_SEARCH_DEPTH;
	short maximumSearchDepth;

	// short** amazons; //amazons, controlled by AI;

	inline float AlfaBeta(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer);
};

