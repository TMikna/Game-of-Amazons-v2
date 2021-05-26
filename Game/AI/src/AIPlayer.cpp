#include "../include/AIPlayer.h"
#include "../include/AlfaBetaAI_fs.h"
#include "../include/AlfaBetaAI_ss.h"
#include "../include/AlfaBetaAI_sssi.h"

void AIPlayer::initiateEvaluation(int evaluation, std::string filename)
{
	switch (evaluation) {
		case 1:
		{
			PossibleMovesEvaluation* evalPME = new PossibleMovesEvaluation();
			this->evaluation = evalPME;
			break;
		}
		case 2:
		{
			DirectionsMovesEvaluation* evalDME = new DirectionsMovesEvaluation();
			this->evaluation = evalDME;
			break;
		}
		case 3:
		{
			CnnEvaluation* evalCnn = new CnnEvaluation(filename);
			this->evaluation = evalCnn;
			break;
		}
		case 4:
		{
			MixedEvaluation* evalMix = new MixedEvaluation(filename);
			this->evaluation = evalMix;
			break;
		}
		 default:
		 {
			 this->evaluation = nullptr;
			 throw "No or non-exsisting evaluation option chosen!";
		 }
	};
}

void AIPlayer::initiateAI(int ai, Board* board, Evaluation* evaluation, UI* ui, short teamColor, short maxDepth)
{
	switch (ai) {
		// case 0 is person
		case 1:
		{
			AlfaBetaAI_fs* fs = new AlfaBetaAI_fs(board, evaluation, ui, teamColor, maxDepth);
			this->ai = fs;
			break;
		}
		case 2:
		{
			AlfaBetaAI_ss* ss = new AlfaBetaAI_ss(board, evaluation, ui, teamColor, maxDepth);
			this->ai = ss;
			break;
		}
		case 3:
		{
			AlfaBetaAI_sssi* sssi = new AlfaBetaAI_sssi(board, evaluation, ui, teamColor, maxDepth);
			this->ai = sssi;
			break;
		}
		default:
		{
			this->ai = nullptr;
			throw "No or non-exsisting player option chosen!";
		}
	};
}