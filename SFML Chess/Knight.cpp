
#include"Utility.h"
#include "Knight.h"
#include<iostream>
using namespace std;

Knight::Knight(Position p, pColor c, Board* b) :Piece(p, c, b)
{
    isFirstMove = false;
}
//void Knight::drawPiece(Position center)
//{
//    gotoRowCol(center.rpos, center.cpos);
//    cout << ((clr == White) ? 'N' : 'n');
//}
#define SQUARE_SIZE 9

void Knight::drawPiece(sf::RenderWindow& window, sf::Vector2f center) {
    sf::Texture texture;
    if (clr == White)
    {
        if (!texture.loadFromFile("images\\white-knight.png")) {
            // Failed to load image
            return;
        }
    }
    else
    {
        if (!texture.loadFromFile("images\\black-knight.png")) {
            // Failed to load image
            return;
        }
    }
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(center);

    window.draw(sprite);
}
////void Knight::drawPiece(Position center) {
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
//    char sym = -37;
//    char sym2 = 222;
//    gotoRowCol(center.rpos, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos, center.cpos + 1);
//    cout << sym;
//    gotoRowCol(center.rpos + 1, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos + 1, center.cpos + 1);
//    cout << sym;
//
//    L2R(center.rpos + 2, center.cpos - 2, center.cpos + 3, sym, fclr);
//    SetClr(fclr, bclr);
//    gotoRowCol(center.rpos - 1, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos - 1, center.cpos + 1);
//    cout << sym;
//    gotoRowCol(center.rpos, center.cpos - 1);
//    cout << sym;
//    gotoRowCol(center.rpos - 1, center.cpos - 1);
//    cout << sym;
//    gotoRowCol(center.rpos - 1, center.cpos - 2);
//    cout << sym;
//
//    L2R(center.rpos - 2, center.cpos - 1, center.cpos + 2, sym, fclr);
//    SetClr(fclr, bclr);
//    gotoRowCol(center.rpos - 1, center.cpos + 2);
//    cout << sym2;
//    gotoRowCol(center.rpos - 1, center.cpos + 3);
//    cout << sym;
//
//    gotoRowCol(center.rpos - 3, center.cpos);
//    cout << sym;
//    gotoRowCol(center.rpos - 3, center.cpos + 1);
//    cout << sym;
//    SetClr(WHITE, BLACK);
//}
bool Knight::legalMove(Board* B, Position S, Position D)
{
    if (S.rpos == D.rpos && S.cpos == D.cpos)
        return false;
    int check = abs(D.rpos - S.rpos); // difference between rows
    int check1 = abs(D.cpos - S.cpos); // difference between columns
    if ((check == 2 && check1 == 1) || (check == 1 && check1 == 2))
    {
        // Knight can make an L-shaped move
        // with two squares in one direction and one square in the other
        return true;
    }
    return false;
}

void Knight::move(Position P)
{
    isFirstMove = true;
    Piece::move(P);
}

bool Knight::FirstMove()
{
    return isFirstMove;
}

/*

  if (D.cpos == S.cpos + 2 && D.rpos == S.rpos + 1) {
        return true;
    }
    if (D.cpos == S.cpos + 2 && D.rpos == S.rpos - 1) {
        return true;
    }
    if (D.cpos == S.cpos - 2 && D.rpos == S.rpos + 1) {
        return true;
    }
    if (D.cpos == S.cpos - 2 && D.rpos == S.rpos - 1) {
        return true;
    }
    if (D.cpos == S.cpos + 1 && D.rpos == S.rpos + 2) {
        return true;
    }
    if (D.cpos == S.cpos + 1 && D.rpos == S.rpos - 2) {
        return true;
    }
    if (D.cpos == S.cpos - 1 && D.rpos == S.rpos + 2) {
        return true;
    }
    if (D.cpos == S.cpos - 1 && D.rpos == S.rpos - 2) {
        return true;
    }
    return false;

*/

PieceType Knight::getType()
{
    return KNIGHT;
}