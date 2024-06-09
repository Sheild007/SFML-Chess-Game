
#ifndef PIECE_H
#define PIECE_H

#include"Utility.h"
#include"Position.h"


class Board;
class Piece
{
protected:
	Position pos;
	Board* B;
	pColor clr;

public:

	Piece(Position p, pColor c, Board* b);
	pColor getColor();
	bool** HighlightLoc(Board* board, Position Sc, int turn);
	bool isMyPiece(Position P, int turn);
	virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center) = 0;
	virtual bool legalMove(Board* B, Position S, Position D) = 0;
	virtual void move(Position P);
	virtual bool FirstMove() = 0;
	static bool isHorizontalMove(Position Sc, Position Dc);
	static bool isVerticalMove(Position Sc, Position Dc);
	static bool isDiagonalMove(Position Sc, Position Dc);
	static bool isMainDiagonalMove(Position Sc, Position Dc);
	static bool isSecDiagonalMove(Position Sc, Position Dc);
	bool verticalPathclear(Position Sc, Position Dc);
	bool HorizentalPathclear(Position Sc, Position Dc);
	bool DignalPathclear(Position Sc, Position Dc);
	virtual PieceType getType() = 0;

};

#endif