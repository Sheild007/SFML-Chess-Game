#ifndef KING_H
#define KING_H

#include "Piece.h"
#include"Utility.h"

class piece;
class King :
    public Piece
{
    bool isFirstMove;
public:
    King(Position p, pColor c, Board* b);
    virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center);
    virtual bool legalMove(Board* B, Position S, Position D);
    virtual bool FirstMove();
    virtual void move(Position P);
    virtual PieceType getType();
};

#endif