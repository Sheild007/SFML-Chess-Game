#include "ChessGameState.h"

ChessGameState::ChessGameState(Board B, Position S, int t, Position D, Players P1, Players P2,bool check,bool checkmate,bool stalemate,bool castling,bool tim)
{

	board = B;
	source = S;
	dest = D;
	turn = t;
	player1 = P1;
	player2 = P2;
	isCheck = check;
	isCheckMate = checkmate;
	isStaleMate = stalemate;
	this->enableCastling = castling;
	timmer = tim;
}
ChessGameState::ChessGameState(const ChessGameState& other)
{
	board = other.board;
	source = other.source;
	dest = other.dest;
	turn = other.turn;
	player1 = other.player1;
	player2 = other.player2;
	isCheck = other.isCheck;
	isCheckMate = other.isCheckMate;
	isStaleMate = other.isStaleMate;
	enableCastling = other.enableCastling;
	this->timmer = other.timmer;

}
void ChessGameState::Update(Board B, Position S, int t, Position D,bool check, bool checkmate, bool stalemate, bool castling,bool tim)
{
	board = B;
	source = S;
	dest = D;
	turn = t;
	isCheck = check;
	isCheckMate = checkmate;
	isStaleMate = stalemate;
	this->enableCastling = castling;
	timmer = tim;
}


