
#pragma once
///
// Unused anymore because it's same as AlfaBetaAI_sssi, only different evaluation.
///

#include "../../include/Player.h"
#include "../../include/UI.h"
class AlfaBetaAI_sssiie :
	public Player
{

public:
	AlfaBetaAI_sssiie(Board* board, UI* ui, short teamColor) :Player(teamColor)
	{
		this->board = board;
		this->ui = ui;
	}
	//Virtual function
	virtual void moveAmazon();
	virtual void shootArrow();
	virtual bool hasPossibleMove();


private:
	UI* ui;
	Board* board;
	Position oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	// short** amazons; //amazons, controlled by AI;

	inline float AlfaBeta(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer);
	inline float AlfaBetaArrow(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer, AmazonMove bestMove);
	inline float Evaluate(Board* board, short nextMovingTeamColor);

};

