#pragma once
#include "Person.h"
#include "../AI/include/RandomAI.h"
#include "../AI/include/AlfaBetaAI_ss.h"
#include "../AI/include/AlfaBetaAI_sssi.h"
#include "../AI/include/AlfaBetaAI_sssiie.h"
#include "../AI/include/AlfaBetaAI_fs.h"
#include "../AI/include/AlfaBetaAI_fs.h"

class Amazons
{
public:
	void loadBoard(std::string boardPath, std::string queensPath, std::string arrowPath, std::string winMsgPath)
	{
		ui.loadBoard(board.getAmazons(), boardPath, queensPath, arrowPath, winMsgPath);
	}
	void play(int gamesAmount);

private:
	Board board;
	UI ui;

};

