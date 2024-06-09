#ifndef BOARD_H
#define BOARD_H
#include"Utility.h"
#include<vector>
using namespace std;
class Piece;
class Players;
class Position;


class Board
{


	Piece* **Ps;
	int rows;
	int cols;
	int Bdim;
	void allocate();
	void copy(const Board&);


public:
	bool enableCastling;
	Piece* getPiece(Position P)const;
	Board();
	Board(int);
	Board(const Board&);
	void init();
	void printBoard(sf::RenderWindow&,int,int,int);
	void DrawOnePiece(Position P);
	void selectPosition(Position&,RenderWindow&);
	bool isValidSource(Position, int);
	bool isValidDest(Position, int);
	void TurnMessage(Players*);
	void movePiece(Position S, Position D);
	bool check(int);
	Position findKing(int);
	Board& operator= (const Board& other);
	bool selfCheck(int);
	bool stalemate(int);
	bool checkmate(int);
	void changeTurn(int& Turn);
	Board* clone();
	void clearBoard();
	void setPiece(Piece* piece, const Position& position);
	void load(ifstream& read);
	void removePiece(Position pos);
	void placePiece(Piece*, Position pos);
	void promote(int, Position, pColor);

};
#endif