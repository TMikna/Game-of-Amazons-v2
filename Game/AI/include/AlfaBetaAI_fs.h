#pragma once
#include "../../include/UI.h"
#include "../include/AI.h"
#include "Evaluations.h"


/// <summary>
/// Alfa-Bera prining AI with full search of moves (compared to another when arrows are searched only for the best amazon)
/// </summary>
class AlfaBetaAI_fs :
    public AI
{
	public:
		AlfaBetaAI_fs(Board* board, Evaluation* evaluation, UI* ui, short teamColor, short maxDepth = c::MAX_SEARCH_DEPTH) :AI(board, ui, teamColor)
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
};
