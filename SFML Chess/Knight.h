#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include"Utility.h"

class Knight :
    public Piece
{
    bool isFirstMove;
public:
    Knight(Position p, pColor c, Board* b);
    virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center);
    virtual bool legalMove(Board* B, Position S, Position D);
    virtual bool FirstMove();
    virtual void move(Position P);
    virtual PieceType getType();
};

#endif