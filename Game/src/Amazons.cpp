#include "../include/Amazons.h"
#include <chrono>  // for high_resolution_clock
#include <fstream>
#include <iostream>


void Amazons::play_BeginFromFile(std::string fileName, std::string outGameFileName, std::string outFileName, std::string metadataName)
{
	std::string gameAsStr;
	std::ifstream myfile(fileName);
	std::ofstream outfile(outFileName);
	std::ofstream outGameFile(outGameFileName);
	if (myfile.is_open())
	{
		int totalGames = 0; // to check if match
		int accpetedGames = 0;
		int discardedGames = 0;
		int whiteWins = 0;
		int	blackWins = 0;
		float wEvalSum = 0;
		float bEvalSum = 0;
		float evalSum = 0;

		auto startTime = std::chrono::high_resolution_clock::now();


		while (std::getline(myfile, gameAsStr))
		{
			reloadBoard();

			// Load  board from file, write dtates to array
			int teamMovedLast = board.loadBoardFromFile(gameAsStr, ui);
			int teamMoveNext = teamMovedLast == BLACKS ? WHITES : BLACKS;


			// Evaluate, which player seems to be in a better position

			DirectionsMovesEvaluation eval;
			// how favourable position is for whites
			float whitesEvaluation = eval.Evaluate(&board, teamMoveNext, WHITES, BLACKS);
			int expextedWinner = -1;

			// 0 is neutral, so we discard games where it's close to zero as it's very likely to be uncertain situation
			// accept if only if it's not so vague 
			if (std::abs(whitesEvaluation) > 0.1) 
			{
				// c::MAX_SEARCH_DEPTH used as default initialization size for depth
				short depthWites = c::MAX_SEARCH_DEPTH;
				short depthBlacks = c::MAX_SEARCH_DEPTH;

				// for some reason this ai (sssi) seems to be playiong the best with depth 2
				if (whitesEvaluation > 0) {
					depthWites = 2;
					depthBlacks = 3;
					expextedWinner = WHITES;
					wEvalSum += whitesEvaluation;
				}
				else {
					depthWites = 3;
					depthBlacks = 2;
					expextedWinner = BLACKS;
					bEvalSum += whitesEvaluation;

				}

				setPW(2, 3, depthWites);
				setPB(2, 3, depthBlacks);

				// Play till the end, and see if weaker player from beteer possition can win - if so, game was finished, we add it to our training data
				int winner = play(false, teamMoveNext, false);

				// if stronger player wins in less favourable position, game is concidered not to have clear winner, thus discarded
				if (winner == expextedWinner)
				{
					// print arrays
					char winnerMarker = winner == WHITES ? 'W' : 'B';
					if (outfile.is_open())
						outfile << winnerMarker << ';' << gameAsStr << '\n';

					if (outGameFile.is_open())
						board.writeBoolBoard (&outGameFile, whitesEvaluation);

					//update info
					
					accpetedGames++;
					if (winner == WHITES)
						whiteWins++;
					else
						blackWins++;
					totalGames++;
				}
				else
				{
					discardedGames++;
					totalGames++;
				}
				
			}
			else
			{
				discardedGames++;
				totalGames++;
			}
			evalSum += std::abs(whitesEvaluation);

			//Print game evaluating status 
			if (totalGames % 100 == 0)
			{
				auto finish = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed = finish - startTime;
				std::cout<<"Evaluated " << totalGames << "games. " << "Elapsed time: " << elapsed.count() << " s\n";
			}

		}
		myfile.close();
		outfile.close();
		outGameFile.close();

		std::ofstream metadataFile(metadataName, std::ios::app);
		if (metadataFile.is_open())
		{
			std::string currentTime = getFormattedTime();
			//metadataFile << "Total games" << ", " << "Accepted games" << ", " << "Discarded games" << ", " << "White wins" <<
			//	", " << "BlackWins" << ", " << "Avg White Eval" << ", " << "Avg Black Eval" << ", " << "Avg Eval (abs icl. discarded)" << 
			//	", " << "Input filename" << ", " << "Output filename" << ", "<< "Date time" <<'\n';

			metadataFile << totalGames << ", " << accpetedGames << ", " << discardedGames << ", " << whiteWins <<
				", " << blackWins << ", " << wEvalSum / whiteWins << ", " << bEvalSum / blackWins << ", " << evalSum / totalGames <<
				", " << fileName << ", " << outGameFileName << ", " << currentTime << '\n';
		}

		//Print Final status 

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - startTime;
		std::cout << "\nFINISHED \n";
		std::cout << "Evaluated total " << totalGames << " games. " << "Elapsed time: " << elapsed.count() << " s\n";
	}
	else
		throw "Unable to open file " + fileName + " to read the game";

}
// not finished
void Amazons::playSeveral(int gamesAmount)
{
	auto start = std::chrono::high_resolution_clock::now();

	int wWins = 0;
	int bWins = 0;

	for (int i = 0; i < gamesAmount; i++)
	{
		auto winner = play(false);
		if (winner == WHITES)
			wWins++;
		else
			bWins++;
		
		reloadBoard();
	}
	//auto winner = play(true);
	//if (winner == WHITES)
	//	wWins++;
	//else
	//	bWins++;
	int totalGames = wWins + bWins;

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "\n\n";
	std::cout << "Elapsed time: " << elapsed.count() << "Avg. time per game: " << elapsed.count()/totalGames << " \n";
	std::cout << "White wins: " << wWins << "   Black wins: " << bWins << " \n";

	std::ofstream outfile("Results.csv", std::ios::app);
	if (outfile.is_open())
	{
	/*	outfile << "Played games" << ',' << "White wins" << ',' << "Black wins" << ',' << "Duration" << ',' << "avg dur/game" << ',' <<
			"White player" << ',' << "White eval" << ',' << "White depth" << ',' <<
			"Black player" << ',' << "Black eval" << ',' << "Black depth" << ',' <<
			"White model name" << ',' << "Black model name" << '\n';*/


		outfile << totalGames << ',' << wWins << ',' << bWins << ',' << elapsed.count() << ',' << elapsed.count() / totalGames << ',' <<
			playerW << ',' << evaluationW << ',' << maxDepthW << ',' <<
			playerB << ',' << evaluationB << ',' << maxDepthB << ',' <<
			filenameW << ',' << filenameB << '\n';
	}
	outfile.close();
}


int Amazons::play(bool waitClose, int teamToStart, bool verbose)
{

	//PossibleMovesEvaluation pme;
	//DirectionsMovesEvaluation dme; 


	//RandomAI rAIw(&board, &ui, WHITES);
	//RandomAI rAIb(&board, &ui, BLACKS);
	//AlfaBetaAI_ss abAIsw(&board, &pme, &ui, WHITES);
	//AlfaBetaAI_ss abAIsb(&board, &pme, &ui, BLACKS);
	//AlfaBetaAI_sssi abAIssw(&board, &pme, &ui, WHITES);
	//AlfaBetaAI_sssi abAIssb(&board, &pme, &ui, BLACKS);
	//AlfaBetaAI_sssi abAIssiw(&board, &dme, &ui, WHITES);
	//AlfaBetaAI_sssi abAIssib(&board, &dme, &ui, BLACKS);
	////AlfaBetaAI_sssiie abAIssiw(&board, &ui, WHITES);
	////AlfaBetaAI_sssiie abAIssib(&board, &ui, BLACKS);
	//AlfaBetaAI_fs abAIfw(&board, &pme, &ui, WHITES);
	//AlfaBetaAI_fs abAIfb(&board, &pme, &ui, BLACKS);

	IPlayer* playerWhite = nullptr;
	IPlayer* playerBlack = nullptr;

	if (playerW == 0)
	{
		//Person PersonW(&board, &ui, WHITES);
		playerWhite = new Person(&board, ui, WHITES);
	}
	else
	{
		playerWhite = new AIPlayer(&board, playerW, evaluationW, ui, WHITES, maxDepthW, filenameW);
	}

	if (playerB == 0)
	{
		playerBlack = new Person(&board, ui, BLACKS);
	}
	else
	{
		playerBlack = new AIPlayer(&board, playerB, evaluationB, ui, BLACKS, maxDepthB, filenameB);
	}

	//playerWhite = new RandomAI(&board, ui, WHITES);

	//Person personw(&board, &ui, WHITES);
	//Person personb(&board, &ui, BLACKS);

	//AIPlayer PlayerWhite(&board, playerW, evaluationW, &ui, WHITES);
	//AIPlayer PlayerBlack(&board, playerB, evaluationB, &ui, BLACKS);

	auto pW = playerWhite;    // player 1 (Whites) 
	auto pB = playerBlack;	  // player 2 (Blacks)

	//std::cout << board.allPossibleDirections(WHITES) << '\n';

	int winner = -1;

	auto start = std::chrono::high_resolution_clock::now();

	if (teamToStart == BLACKS)
	{
		if (pB->hasPossibleMove())
		{
			pB->makeMove();
		}
		else
		{
			ui->displayWinner(pW->getTeamColor()); // p2 ran out of moves, p1 wins
			winner = WHITES;
			board.isGameFinished = true;
			if(verbose)
				std::cout << "pW wins" << std::endl;
		}
	}


	while (!board.isGameFinished)
	{
		if (pW->hasPossibleMove())
		{
			pW->makeMove();
		}
		else
		{
			ui->displayWinner(pB->getTeamColor()); // p1 ran out of moves, p2 wins
			winner = BLACKS;
			board.isGameFinished = true;
			if (verbose)
				std::cout << "pB wins" << std::endl;
			break;
		}

		//	std::chrono::milliseconds timespan(2000); // or whatever
		//	std::this_thread::sleep_for(timespan);

		if (pB->hasPossibleMove())
		{
			pB->makeMove();
		}
		else
		{
			ui->displayWinner(pW->getTeamColor()); // p2 ran out of moves, p1 wins
			winner = WHITES;
			board.isGameFinished = true;
			if (verbose)
				std::cout << "pW wins" << std::endl;
			break;
		}
		//	std::this_thread::sleep_for(timespan);
	}

	if (verbose)
	{
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	}

	// keep the window open after game finishes. Turn of when automatically palay series of games
	if (waitClose)
		ui->waitClose();


	return winner;
}


std::string Amazons::getFormattedTime()
{
	time_t rawtime;
	struct tm timeinfo;
	char TimeBuffer[18];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(TimeBuffer, 18, "%F %R", &timeinfo);
	return TimeBuffer;
}