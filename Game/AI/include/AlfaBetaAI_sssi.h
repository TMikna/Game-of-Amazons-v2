#pragma once
#include "../../include/Player.h"
#include "../../include/UI.h"
#include "Evaluations.h"
#include "AI.h"
class AlfaBetaAI_sssi :
    public AI
{

public:
	AlfaBetaAI_sssi(Board* board, Evaluation* evaluation, UI* ui, short teamColor, short maxDepth = c::MAX_SEARCH_DEPTH) :AI(board, ui, teamColor)
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
	short maximumSearchDepth;

	// short** amazons; //amazons, controlled by AI;

	inline float AlfaBeta(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer);
	inline float AlfaBetaArrow(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer, AmazonMove bestMove);

};

