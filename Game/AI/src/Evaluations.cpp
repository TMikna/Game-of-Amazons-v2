#include "../include/Evaluations.h"

// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
float PossibleMovesEvaluation::Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor)
{
	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	short movCount = board->countAllMoves(teamColor);
	short enemyMovCount = board->countAllMoves(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float evaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position
	return evaluation; 
}

// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
inline float DirectionsMovesEvaluation::Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor)
{

	float cof1 = 0.3f;
	float cof2 = 1 - cof1;

	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	short movCount = board->countAllMoves(teamColor);
	short enemyMovCount = board->countAllMoves(oppositeTeamColor);

	short movDirections = board->allPossibleDirections(teamColor);
	short enemyMovDirections = board->allPossibleDirections(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float mowEvaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position

	float dirEvaluation = (float(movDirections - enemyMovDirections) + bias) / (float(movDirections + enemyMovDirections) + std::abs(bias));

	float evaluation = cof1 * mowEvaluation + cof2 * dirEvaluation;

	return evaluation;
}