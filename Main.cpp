//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs

#include "Game//include/Amazons.h"
#include <chrono>  // for high_resolution_clock
#include <iostream>


int main()
{
	Amazons amazons;

	//////////////
	//Evaluations: 
	//	0 - no evaluation (payler is person)
	//  1 -
	//  2 - 
	//Players:
	//	0 - person
	//	1 - Full search Alpha Beta (AlfavetaAI_fs)
	//	2 - 
	// 	3 -
	///////////////

    amazons.loadImages("images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");

	// setPW and PD done inside the function, depending on situation afrer loading game in file
	amazons.play_BeginFromFile("../Notebooks/Data/p10_clean.txt", "p10_boards.txt", "p10_Out.txt");

	
	//short evaluationW = 2;
	//short PlayerW = 3;

	//short evaluationB = 2;
	//short PlayerB = 3; 

	//amazons.setPW(evaluationW, PlayerW, 2);    
	//amazons.setPB(evaluationB, PlayerB, 4);
	//
	//amazons.play(true);











	//Board boardX;
	//BoardArray testBoardState =
	//{ 0, -1, 2, 2,
	//0, 1, 1, -1,
	//0, 0, 0, 0,
	//0, 0, 0, 0, };
	////{ 2, -1, -1, -1,
	////  -1, -1, -1, 0,
	////  0, 2, -1, 1,
	////  1, 0, -1, 0, };

	//{
	//	boardX.setBoardState(testBoardState);
	//	std::vector <AmazonMove> possibleMoves = boardX.findAllMoves(BLACKS);

	//	bool X = boardX.hasMove(BLACKS);
	//}


	//Ai ai2(&board, &ui, WHITES);

	
	//board.findAllMoves(BLACKS);

	//auto moves = board.findAllMoves(WHITES);
	//ai.moveAmazon();

	
/*
	int randomCount = 0;
	int AlfaBetaCount = 0;

	for (int i = 0; i < 200; i++)
	{
		Board board;
		UI ui;
		RandomAI rAIw(&board, &ui, WHITES);
		AlfaBetaAI_ss abAIb(&board, &ui, BLACKS);
		ui.loadBoard(board.getAmazons(), "images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");
		auto p1 = rAIw;    // player 1 (Whites)
		auto p2 = abAIb;		// player 2 (Blacks)

		while (ui.window.isOpen())
		{
			if (p1.hasPossibleMove())
			{
				p1.makeMove();
			}
			else
			{
				ui.displayWinner(p2.getTeamColor()); // p1 ran out of moves, p2 wins
				//std::cout << "p2 wins" << std::endl;
				AlfaBetaCount++;
				break;
			}

			if (p2.hasPossibleMove())
			{
				p2.makeMove();
			}
			else
			{
				ui.displayWinner(p1.getTeamColor()); // p2 ran out of moves, p1 wins
				//std::cout << "p1 wins" << std::endl;
				randomCount++;
				break;
			}

		}		
		
		if (i % 10 == 0)
		{		
			std::cout << "Iteration:         " << randomCount << std::endl;
			std::cout << "Random AI wins:    " << randomCount << std::endl;
			std::cout << "AlphaBeta AI wins: " << AlfaBetaCount << std::endl;
			std::cout << std::endl;
		}
		ui.closeWindow();
	}
//	ui.waitClose();
		std::cout << std::endl;
		std::cout << "Final result:      " << std::endl;
		std::cout << "Random AI wins:    " << randomCount << std::endl;
		std::cout << "AlphaBeta AI wins: " << AlfaBetaCount << std::endl;
		std::cout << std::endl;

*/
	return 0;
}
