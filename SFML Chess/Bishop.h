
#ifndef BISHOP_H
#define BISHOP_H
#include"Utility.h"
#include "Piece.h"
class Bishop :
    public Piece
{
    bool isFirstMove;
public:
    Bishop(Position p, pColor c, Board* b);
   virtual void drawPiece(sf::RenderWindow& window, sf::Vector2f center);
    virtual bool legalMove(Board* B, Position S, Position D);
    virtual bool FirstMove();
    virtual void move(Position P);
    virtual PieceType getType();
};
#endif
