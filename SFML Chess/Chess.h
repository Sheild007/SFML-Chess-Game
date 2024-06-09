#ifndef CHESS_H
#define CHESS_H
#include"Position.h"
#include"Utility.h"
#include<vector>
#include"ChessGameState.h"
using namespace std;
class Board;

class Players;
class Chess
{
private:
	Position sourcePos;
	Position destPos;
	Players* players[2];
	//bool legalMoveMap[8][8];
	Board* B;
	int rows;
	int cols;
	int turn;
	void write(ChessGameState last);
	RenderWindow* window;
	bool inRange(int x, int y);
	bool renderHiglight;
	bool selectDest;
	Board* Copy;
	int boxSize;
	int shift_X;
	int shift_Y;
	void action();
	bool isCheck;
	bool isCheckMate;
	bool isStaleMate;
	void undoGame(vector<ChessGameState>& gameHistory, int index);
	void RedoGame(vector<ChessGameState>& gameHistory, int index);
	bool isPromotion(Position pos);
	void promotion(Position pos);
	void safe(vector<ChessGameState> gameHistory);
	bool Load;
	bool timer;
	int p1Time;
	int p2Time;
public:
	Chess();
	void InputNames();
	void Play();
	void load();	
};

#endif