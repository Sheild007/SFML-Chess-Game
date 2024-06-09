
#include "Pawn.h"
#include"Utility.h"
#include"Board.h"
#include <iostream>
using namespace std;

Pawn::Pawn(Position p, pColor c, Board* b) : Piece(p, c, b)
{
    isFirstMove = true;

}
void Pawn::drawPiece(sf::RenderWindow& window, sf::Vector2f center) {
    sf::Texture texture;
    if (clr == White)
    {
        if (!texture.loadFromFile("images\\white-pawn.png")) {
            // Failed to load image
            return;
        }
    }
    else
    {
        if (!texture.loadFromFile("images\\black-pawn.png")) {
            // Failed to load image
            return;
        }
    }
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(center);

    window.draw(sprite);
}
void Circle(int h, int k, float radius, char sym, int clr)
{

    for (int theta = 0; theta < 360; theta++)
    {
        SetClr(clr, BLACK);
        float rad = theta * 3.1415 / 180;
        float x = ceil(radius * cos(rad)) + k;
        float y = ceil(radius * sin(rad)) + h;
        gotoRowCol(y, x);
        cout << sym;
    }
}
//void Pawn::drawPiece(Position center)
//{
//    int bclr;
//    if ((center.rpos + center.cpos) % 2 == 0)
//        bclr = LightGrey
//        ;
//    else
//        bclr = Grey;
//    if (clr == White)
//    {
//        SetClr(WHITE, bclr);
//        Circle(center.rpos, center.cpos, 2.1, -37, WHITE);
//        Circle(center.rpos, center.cpos, 1, -37, WHITE);
//    }
//    else if (clr == Black)
//    {
//        SetClr(BLACK, bclr);
//        Circle(center.rpos, center.cpos, 2.1, -37, BLACK);
//        Circle(center.rpos, center.cpos, 1, -37, BLACK);
//    }
//    SetClr(WHITE, BLACK);
//}
bool Pawn::legalMove(Board* B, Position S, Position D)
{
    if (S.rpos == D.rpos && S.cpos == D.cpos)
        return false;
    // Determine the direction of the pawn's movement based on its color
    int dir = (clr == White) ? -1 : 1;

    // Check if the pawn is moving one or two spaces forward
    if (S.cpos == D.cpos && (D.rpos - S.rpos == dir || (S.rpos == 1 && D.rpos == 3 && dir == 1) || (S.rpos == 6 && D.rpos == 4 && dir == -1)))
    {
        // Check if the destination space is unoccupied
        if (B->getPiece(D) == nullptr)
        {
            if (!verticalPathclear(S, D))
                return false;

            if (isFirstMove && abs(D.rpos - S.rpos) == 2)
            {
                isFirstMove = false;
            }
            else if (isFirstMove) {
                isFirstMove = false;
            }
            return true;
        }
    }
    // Check if the pawn is capturing an opponent's piece
    else if (abs(S.cpos - D.cpos) == 1 && D.rpos - S.rpos == dir)
    {
        // Check if the destination space is occupied by an opponent's piece
        Piece* p = B->getPiece(D);
        if (p != nullptr && p->getColor() != clr)
        {
            isFirstMove = false;
            return true;
        }
    }

    // The move is not legal
    return false;
}
void Pawn::move(Position P)
{
    isFirstMove = false;
    Piece::move(P);
}
bool Pawn::FirstMove()
{
    return isFirstMove;
}

PieceType Pawn::getType()
{
    return PAWN;
}