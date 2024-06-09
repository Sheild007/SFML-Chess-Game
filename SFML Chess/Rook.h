#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include"Utility.h"
class Rook :
    public Piece
{
    bool isFirstMove;

public:
    Rook(Position p, pColor c, Board* b);
    virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center);
    virtual bool legalMove(Board* B, Position S, Position D);
    virtual bool FirstMove();
    virtual void move(Position P);
    virtual PieceType getType();
};
#endif
