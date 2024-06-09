
#include "Rook.h"
#include"Utility.h"
#include<iostream>
using namespace std;

Rook::Rook(Position p, pColor c, Board* b) :Piece(p, c, b)
{
    isFirstMove = false;
}
//void Rook::drawPiece(Position center)
//{
//	gotoRowCol(center.rpos, center.cpos);
//	cout << ((clr == White) ? 'R' : 'r');
//}
# define SQUARE_SIZE 9
//void Rook::drawPiece(Position center) {
//    short x = center.cpos;
//    short y = center.rpos;
//    int fclr, bclr;
//    if (clr == White)
//        fclr = WHITE;
//    else
//        fclr = BLACK;
//    if ((center.rpos + center.cpos) % 2 == 0)
//        bclr = LightGrey
//        ;
//    else
//        bclr = Grey;
//    SetClr(fclr, bclr);
//
//
//
//
//    char sym = -37;
//    gotoRowCol(center.rpos, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos, center.cpos + 1);
//    cout << sym;
//    gotoRowCol(center.rpos + 1, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos + 1, center.cpos + 1);
//    cout << sym;
//
//
//    L2R(center.rpos - 1, center.cpos - 2, center.cpos + 3, sym, fclr);
//    L2R(center.rpos + 2, center.cpos - 2, center.cpos + 3, sym, fclr);
//    L2R(center.rpos - 2, center.cpos - 3, center.cpos + 4, sym, fclr);
//    L2R(center.rpos + 3, center.cpos - 3, center.cpos + 4, sym, fclr);
//    SetClr(WHITE, BLACK);
//}
void Rook::drawPiece(sf::RenderWindow& window, sf::Vector2f center) {
    sf::Texture texture;
    if (clr == White)
    {
        if (!texture.loadFromFile("images\\white-rook.png")) {
            // Failed to load image
            return;
        }
    }
    else
    {
        if (!texture.loadFromFile("images\\black-rook.png")) {
            // Failed to load image
            return;
        }
    }
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(center);

    window.draw(sprite);
}
void Rook::move(Position P)
{
    isFirstMove = true;
    Piece::move(P);
}

bool Rook::legalMove(Board* B, Position S, Position D)
{
    if (S.rpos == D.rpos && S.cpos == D.cpos)
        return false;

    return ((isVerticalMove(S, D) && (verticalPathclear(S, D))) || (isHorizontalMove(S, D) && HorizentalPathclear(S, D)))
        ;
}

bool Rook::FirstMove()
{
    return isFirstMove;
}
PieceType Rook::getType()
{
    return ROOK;
}