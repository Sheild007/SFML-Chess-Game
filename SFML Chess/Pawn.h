#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include"Utility.h"

class Pawn :
    public Piece
{
    bool isFirstMove;
public:
    Pawn(Position p, pColor c, Board* b);
    virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center);
    virtual bool legalMove(Board* B, Position S, Position D);
    virtual bool FirstMove();
    virtual void move(Position P);
    virtual PieceType getType();


};

#endif