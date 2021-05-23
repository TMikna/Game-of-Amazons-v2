#pragma once
#include "Person.h"
#include "../AI/include/RandomAI.h"
#include "../AI/include/AlfaBetaAI_ss.h"
#include "../AI/include/AlfaBetaAI_sssi.h"
#include "../AI/include/AlfaBetaAI_sssiie.h"
#include "../AI/include/AlfaBetaAI_fs.h"
#include "../AI/include/AlfaBetaAI_fs.h"
#include "../AI/include/AIPlayer.h"

class Amazons
{
public:

	void setPW(short eval, short player, short maxDepth = c::MAX_SEARCH_DEPTH, std::string filename = "") {
		evaluationW = eval;
		playerW = player;
		maxDepthW = maxDepth;
		filenameW = filename;
	}
	void setPB(short eval, short player, short maxDepth = c::MAX_SEARCH_DEPTH, std::string filename = "") {
		evaluationB = eval;
		playerB = player;
		maxDepthB = maxDepth;
		filenameB = filename;

	}

	void loadImages(std::string boardPath, std::string queensPath, std::string arrowPath, std::string winMsgPath)
	{
		ui->loadBoard(board.getAmazons(), boardPath, queensPath, arrowPath, winMsgPath);
		this->boardPath = boardPath;
		this->queensPath = queensPath;
		this->arrowPath = arrowPath;
		this->winMsgPath = winMsgPath;
	}

	void reloadBoard()
	{
		Board newBoard;
		board = newBoard;
		delete ui;
		ui = new UI;
		ui->loadBoard(board.getAmazons(), boardPath, queensPath, arrowPath, winMsgPath);
	}
	
	int play(bool waitClose, int teamToStart = WHITES, bool verbose = true);
	void playSeveral(int gamesAmount);
	void play_BeginFromFile(std::string fileName, std::string outGameFileName = "", std::string outFileName = "", std::string metadataName = "GameFinishingInfo.csv");


private:
	Board board;
	UI* ui =  new UI;

	short evaluationW = -1;
	short playerW = -1;
	short maxDepthW = c::MAX_SEARCH_DEPTH;
	std::string filenameW = "";

	short evaluationB = -1;
	short playerB = -1;
	short maxDepthB = c::MAX_SEARCH_DEPTH;
	std::string filenameB = "";


	std::string boardPath; 
	std::string queensPath;
	std::string arrowPath;
	std::string winMsgPath;

	std::string getFormattedTime();

};