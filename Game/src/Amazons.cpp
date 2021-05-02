#include "../include/Amazons.h"
#include <chrono>  // for high_resolution_clock


void Amazons::play(int gamesAmount)
{
	PossibleMovesEvaluation pme;
	//DirectionsMovesEvaluation dme;

	Person personw(&board, &ui, WHITES);
	Person personb(&board, &ui, BLACKS);
	RandomAI rAIw(&board, &ui, WHITES);
	RandomAI rAIb(&board, &ui, BLACKS);
	AlfaBetaAI_ss abAIsw(&board, &pme, &ui, WHITES);
	AlfaBetaAI_ss abAIsb(&board, &pme, &ui, BLACKS);
	AlfaBetaAI_sssi abAIssw(&board, &pme, &ui, WHITES);
	AlfaBetaAI_sssi abAIssb(&board, &pme, &ui, BLACKS);
	//AlfaBetaAI_sssi abAIssiw(&board, &dme, &ui, WHITES);
	//AlfaBetaAI_sssi abAIssib(&board, &dme, &ui, BLACKS);
	//AlfaBetaAI_sssiie abAIssiw(&board, &ui, WHITES);
	//AlfaBetaAI_sssiie abAIssib(&board, &ui, BLACKS);
	AlfaBetaAI_fs abAIfw(&board, &pme, &ui, WHITES);
	AlfaBetaAI_fs abAIfb(&board, &pme, &ui, BLACKS);



	auto pW = abAIfw; // player 1 (Whites)
	auto pB = rAIb;	  // player 2 (Blacks)

	//auto pW = abAIssiw; // player 1 (Whites)
	//auto pB = abAIssb;	  // player 2 (Blacks)

	std::cout << board.allPossibleDirections(WHITES) << '\n';

	auto start = std::chrono::high_resolution_clock::now();

	while (ui.window.isOpen())
	{
		if (pW.hasPossibleMove())
		{
			pW.makeMove();
		}
		else
		{
			ui.displayWinner(pB.getTeamColor()); // p1 ran out of moves, p2 wins
			std::cout << "pB wins" << std::endl;
			break;
		}

		//	std::chrono::milliseconds timespan(2000); // or whatever
		//	std::this_thread::sleep_for(timespan);

		if (pB.hasPossibleMove())
		{
			pB.makeMove();
		}
		else
		{
			ui.displayWinner(pW.getTeamColor()); // p2 ran out of moves, p1 wins
			std::cout << "pW wins" << std::endl;
			break;
		}
		//	std::this_thread::sleep_for(timespan);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	ui.waitClose();



}
