#pragma once
#include "../../include/Player.h"
#include "../../include/UI.h"
#include "Evaluations.h"
#include "AI.h"

class AIPlayer :
    public IPlayer
{
public:
	AIPlayer(Board* board, AI* ai, Evaluation* evaluation, UI* ui, short teamColor)
	{
		
		this->evaluation = evaluation;
		this->ai = ai; 
	} 

	AIPlayer(Board* board, int ai, int eval, UI* ui, short teamColor, short maxDepth, std::string filename = "")
	{
		initiateEvaluation(eval, filename);   // evaluation should be initiated first  
		initiateAI(ai, board, evaluation, ui, teamColor, maxDepth);
	}
	 
	//Virtual function
	virtual void moveAmazon() { ai->moveAmazon(); };
	virtual void shootArrow() { ai->shootArrow(); };
	virtual bool hasPossibleMove() { return ai->hasPossibleMove(); };
	virtual void makeMove() { ai->makeMove(); };
	virtual short getTeamColor() { return ai->getTeamColor(); };

private:


	Evaluation* evaluation;
	AI* ai;
	// short** amazons; //amazons, controlled by AI;

	//inline float AlfaBeta(Board * searchBoard, short depth, float alpha, float beta, bool maximizingPlayer);

	void initiateAI(int ai, Board* board, Evaluation* evaluation, UI* ui, short teamColor, short maxDepth);
	void initiateEvaluation(int evaluation, std::string filename = "");

};

 