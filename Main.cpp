//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs

#include "Game//include/Amazons.h"
#include <chrono>  // for high_resolution_clock
#include <iostream>

#include <fdeep/fdeep.hpp>

int main()
{
	Amazons amazons;

	//////////////
	//Evaluations: 
	//	0 - no evaluation (payler is person)
	//  1 - PossibleMovesEvaluation
	//  2 - DirectionsMovesEvaluation
	//Players:
	//	0 - person
	//	1 - Full search Alpha Beta (AlfavetaAI_fs)
	//	2 - 
	// 	3 -
	///////////////

    amazons.loadImages("images/Board10x10.png", "images/queens2.png", "images/arrow.png", "images/winMsg.png");

	// setPW and PD done inside the function, depending on situation afrer loading game in file
	//amazons.play_BeginFromFile("../Notebooks/Data/p10_clean.txt", "p10_boards_4d_eval.txt", "p10_Out_4d_eval.txt");

	//fw - first working
	short evaluationW = 3;
	short PlayerW = 3;
	// used only with CNN evaluation (evaluation = 3, 4)
	//std::string modelW = "fdeep_model.json";

	short evaluationB = 3;
	short PlayerB = 3;
	// used only with CNN evaluation (evaluation = 3, 4)


	//std::string modelW = "NaN";
	//std::string modelB = "NaN";
	std::string modelW = "fdeep_model_first.json";
	std::string modelB = "fdeep_model_first.json";
	
	//std::string modelB = "fdeep_model_EP_30_BS_64_LR_0.02_DU_128_DU2_128_DU3_128_SGD_ca_relu_da_relu_oa_sigmoid_loss_mse_KR_none_DR1_0.2_DR2_0.2_f1_32_f2_32_f3_32_mixedData.json";

	//amazons.setPW(evaluationW, PlayerW, 3, modelW);
	//amazons.setPB(evaluationB, PlayerB, 3, modelB);
	//
	//amazons.playSeveral(100);

	//amazons.play(true);

	short wEvals[3] = { 1,2,3 };
	short bEvals[3] = { 1,2,3 };

	for (auto wp : wEvals)
	{
		for (auto bp : bEvals)
		{
			short evaluationW = wp;
			short PlayerW = 3;

			short evaluationB = bp;
			short PlayerB = 3;

			amazons.setPW(evaluationW, PlayerW, 3, modelW);
			amazons.setPB(evaluationB, PlayerB, 3, modelB);

			amazons.playSeveral(20);
		}
	}



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
