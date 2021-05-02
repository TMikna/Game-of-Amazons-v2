#pragma once
#include "../../include/UI.h"
#include "../../include/Player.h"
#include "Evaluations.h"


/// <summary>
/// Alfa-Bera prining AI with full search of moves (compared to another when arrows are searched only for the best amazon)
/// </summary>
class AlfaBetaAI_fs :
    public Player
{
	public:
		AlfaBetaAI_fs(Board* board, Evaluation* evaluation, UI* ui, short teamColor) :Player(teamColor)
		{
			this->board = board;
			this->ui = ui;
			this->evaluation = evaluation;
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

