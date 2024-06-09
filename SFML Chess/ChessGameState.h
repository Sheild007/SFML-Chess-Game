#ifndef CHESSGAMESTATE_H
#define CHESSGAMESTATE_H
#include"Utility.h"
#include"Board.h"
#include"Players.h"
class Board;
class Players;
class ChessGameState
{
public:
	Board board;
	Position source;
	Position dest;
	int turn;
	Players player1;
	Players player2;
	bool isCheck;
	bool isCheckMate;
	bool isStaleMate;
	bool enableCastling;
	bool timmer;

	ChessGameState(Board B, Position S, int t, Position D, Players P1, Players P2,bool check,bool checkmate,bool staltemate,bool castling,bool);
	ChessGameState(const ChessGameState& other);
	void Update(Board B, Position S, int t, Position D,bool check,bool checkmate,bool stalemate,bool castling,bool);

};
#endif


