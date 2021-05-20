#pragma once
#include "..\include\Board.h"

Position Board::parsePosition(std::string gameStr, unsigned long index)
{
	int y = gameStr[index] - 97;
	if (y < 0 || y >10)
		throw "Unexpected symbor parsing game at index" + std::to_string(index) +
		" Got " + gameStr[index] + " Expected a letter between a and j";
	index++;

	// boar is numbered bottom to top, while in the system - top to botttom
	int  x = 9 - (std::stoi(gameStr.substr(index, 2)) -1); 
	Position pos(x, y); 

	index++;
	if (gameStr[index] != '-' && gameStr[index] != '/' && gameStr[index] != ']')
		index++;
	if (gameStr[index] != '-' && gameStr[index] != '/' && gameStr[index] != ']')
		throw "unexpected symbol. Expected: '-', '/' or ']'";

	return pos;
}