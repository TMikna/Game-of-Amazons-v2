#include "..\include\AlfaBetaAI_sssi.h"

void AlfaBetaAI_sssi::moveAmazon()
{
	short maxDepth = maximumSearchDepth;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove nextMove;

#pragma region Modilied 1st half of 1st layer of alfa-beta search
	float maxEva = -std::numeric_limits<float>::max();		// -infinity (closest we can get)
	//if (!board->hasMove(teamColor))						//Lost, should never get here
	float alpha = -std::numeric_limits<float>::max();		// -infinity (closest we can get) 
	float beta = std::numeric_limits<float>::max();			// +infinity (closest we can get)

	auto possibleMoves = boardCopy.findAllMoves(teamColor);
	for (auto& move : possibleMoves)						// access by reference to avoid copying
	{
		boardCopy.moveAmazon(move.from, move.to);
		float evaluation = AlfaBetaArrow(&boardCopy, maxDepth, alpha, beta, true, move);
		if (evaluation >= maxEva)
		{
			maxEva = evaluation;
			nextMove = move;
		}
		boardCopy.moveAmazon(move.to, move.from);			//undo move before exiting
		// alfa-beta pruning
		alpha = std::max(alpha, maxEva);
		if (alpha >= beta)
			break;
	}
#pragma endregion

	//AmazonMove move = moves[chooseMove(moveCount)];
	//AmazonMove move = AlfaBeta();

	oldPos = nextMove.from;
	newPos = nextMove.to;

	ui->changeAmazonPosition(oldPos, newPos);
	board->moveAmazon(oldPos, newPos);
}

void AlfaBetaAI_sssi::shootArrow()
{
	short maxDepth = maximumSearchDepth;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove arrowShoot;

#pragma region Modilied 2nd half of 1st layer of alfa-beta search
	float maxEvaArrow = -std::numeric_limits<float>::max();              // -infinity (closest we can get)
	float alpha = -std::numeric_limits<float>::max();					 // -infinity (closest we can get)
	float beta = std::numeric_limits<float>::max();						 // +infinity (closest we can get)
	auto possibleArrows = boardCopy.findAllMovesFrom(newPos);
	for (auto& move : possibleArrows)                                    // access by reference to avoid copying
	{
		boardCopy.placeArrow(move.to);
		float evaluation = AlfaBeta(&boardCopy, maxDepth - 1, alpha, beta, false);
		if (evaluation >= maxEvaArrow)
		{
			maxEvaArrow = evaluation;
			arrowShoot = move;
		}
		boardCopy.undoArrow(move.to);									 //undo move before exiting

		// alfa-beta pruning
		alpha = std::max(alpha, maxEvaArrow);
		if (alpha >= beta)
			break;
	}
#pragma endregion
	arrowPos = arrowShoot.to;

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}


// Is it better to find best move and then best arrow shot for it - CURRENT
// AlfaBetaArrow() is second half of it
inline float AlfaBetaAI_sssi::AlfaBeta(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }

	if (maximizingPlayer)      // for Maximizer Player  
	{
		if (depth == 0 || !searchBoard->hasMove(teamColor))					// Reached decsired depth or end of the game
			return evaluation->Evaluate(searchBoard, teamColor, teamColor, oppositeTeamColor);

		// it is not deeded in arriw part, because it gets into arroiw parf from amazon part and here depth is not reduced, also game cannot end

		//AmazonMove bestMove;
		float maxEva = -std::numeric_limits<float>::max();					// -infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(teamColor);

		for (auto& move : possibleMoves)									// access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);
			float evaluation = AlfaBetaArrow(searchBoard, depth, alpha, beta, true, move);
			if (evaluation > maxEva)
			{
				maxEva = evaluation;
				//bestMove = move;
			}
			searchBoard->moveAmazon(move.to, move.from);					 //undo move before exiting

			// alfa-beta pruning
			alpha = std::max(alpha, maxEva);
			if (alpha >= beta)
				break;

			return maxEva;
		}
	}

	else
	{	// for Minimizer player  
		if (depth == 0 || !searchBoard->hasMove(oppositeTeamColor))				// Reached decsired depth or end of the game
			return evaluation->Evaluate(searchBoard, oppositeTeamColor, teamColor, oppositeTeamColor);

			// it is not deeded in arrow part, because it gets into arroiw parf from amazon part and here depth is not reduced, also game cannot end


		//AmazonMove worstMove;
		float minEva = std::numeric_limits<float>::max();						 // +infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(oppositeTeamColor);

		for (auto& move : possibleMoves)										 // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);
			float evaluation = AlfaBetaArrow(searchBoard, depth, alpha, beta, false, move);
			if (evaluation < minEva)
			{
				minEva = evaluation;
				//worstMove = move;
			}
			searchBoard->moveAmazon(move.to, move.from);						 //undo move before exiting	

			// alfa-beta pruning
			beta = std::min(beta, minEva);
			if (alpha >= beta)
				break;

			return minEva;
		}
	}
}


inline float AlfaBetaAI_sssi::AlfaBetaArrow(Board* searchBoard, short depth, float alpha, float beta, bool maximizingPlayer, AmazonMove move)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }

	if (maximizingPlayer)      // for Maximizer Player  
	{
		float maxEvaArrow = -std::numeric_limits<float>::max();						// -infinity (closest we can get)
		auto possibleArrows = searchBoard->findAllMovesFrom(move.to);
		for (auto& move : possibleArrows)											// access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);
			float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, false);
			maxEvaArrow = std::max(maxEvaArrow, evaluation);						//gives Maximum of the values  
			searchBoard->undoArrow(move.to);										//undo move before exiting?

			// alfa-beta pruning
			alpha = std::max(alpha, maxEvaArrow);
			if (alpha >= beta)
				break;
		}
		return maxEvaArrow;
		//Returning arrow evaluation because it is board state evaluation after whole move
	}

	else
	{	// for Minimizer player  
		
		float minEvaArrow = std::numeric_limits<float>::max();			    // +infinity (closest we can get with float)
		auto possibleArrows = searchBoard->findAllMovesFrom(move.to);

		for (auto& move : possibleArrows)								    // access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);								//place arrow
			float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, true);
			minEvaArrow = std::min(minEvaArrow, evaluation);
			searchBoard->undoArrow(move.to);	                            //undo arrow before exiting	

			// alfa-beta pruning
			beta = std::min(beta, minEvaArrow);
			if (alpha >= beta)
				break;
		}
		return minEvaArrow;
	}
}

bool AlfaBetaAI_sssi::hasPossibleMove()
{
	return board->hasMove(teamColor);
}
