#pragma once
#include "../../include/Player.h"
#include "../../include/UI.h"
#include "Evaluations.h"


class AlfaBetaAI_ss :
    public Player
{

public:
	AlfaBetaAI_ss(Board* board, Evaluation* evaluation, UI* ui, short teamColor):Player(teamColor)
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
	Evaluation* evaluation;

	// short** amazons; //amazons, controlled by AI;

	inline float AlfaBeta(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer);
};

