#pragma once
#include "Constants.h"
#include "AmazonMove.h"
#include <array>
#include <deque>
#include <vector>
#include <string>
// for loanding the board from file - board makes moves itself so need to update ui too.
#include "../include/UI.h"


class Board
{
public:

    Board() { setAmazonsArrays(); };
    Board(BoardArray boardState) { this->board = boardState; setAmazonsArrays(); };
    void moveAmazon(Position oldPos, Position newPos);
    bool isMoveAllowed(Position oldPos, Position newPos);
    void placeArrow(Position pos) { 
        board[pos.x][pos.y] = -1; 
        boolBoard[pos.x][pos.y][2] = true; 
        boolBoard[pos.x][pos.y][3] = true;
        moveCount++;
    };
    void undoArrow(Position pos) { board[pos.x][pos.y] = 0; };
    short getPlayer(Position pos) { return board[pos.x][pos.y]; };
    short** getAmazons();
    short** getAmazons(short teamColor);
    short possibleDirections(Position amazon);
    short allPossibleDirections(short teamColor);


    //All moves finding is a bit messy, might be nicer if I saves queens in separate arrays too, but for now decided to leave all logic on board array
    //Probably it's still possible to implement it nicer

//    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Position[0] to Position[1])
    std::vector<AmazonMove> findAllMoves(short teamColor); //find all allowd player amazons moves (from Position[0] to Position[1])
//    std::vector<AmazonMove> findAllMovesFrom(Vector2i pos, std::vector<AmazonMove>* moves = NULL);
    std::vector<AmazonMove> findAllMovesFrom(Position pos);
    short countAllMoves(short teamColor);  // same as finding, but instead counting only (for performance improvement)
    short countAllMovesFrom(Position pos, short*movesCount = NULL);

    bool hasMove(short teamColor);
    bool hasMove(Position amazon);

    int loadBoardFromFile(std::string gameAsStr, UI* ui = nullptr);


    void printBoard();

    BoardArray getBoardState() { return board; };
    //currently unused
    void setBoardState(BoardArray board) { this->board = board; setAmazonsArrays();
    };

    Position parsePosition(std::string gameStr, unsigned long index);
    void writeBoolBoard(std::ofstream *file, float winnerNotation);

    BoolBoardArray boolBoard = setInitialBoolBoard();
    bool isGameFinished = false;

    //how many times amazons were moved, both players counted in, arrow shooting not counted in, updated after arrow shot
    int moveCount = 0;
private:
    BoardArray board = init::INITIAL_BOARD;
    // third dimention: [0] - for Whites amazons, [1] - black amazons, [2] - for arrows, do we need one more for empty spaces? 
    
    // used while loading board from file, since those arev the only states we need for training
    std::vector<BoolBoardArray> boardStates; // saves board state after every move

    std::vector<Position> wAmazonsPositions;
    std::vector<Position> bAmazonsPositions;

    void setAmazonsArrays();
    bool isQueenTrajectory(Position oldPos, Position newPos);
    inline bool isOnBoard(Position pos);
    inline void findAllMovesFrom(Position pos, std::vector<AmazonMove>* moves); //for findAllMoves method
    BoolBoardArray setInitialBoolBoard();

    ///////////
    // Helpers

};

