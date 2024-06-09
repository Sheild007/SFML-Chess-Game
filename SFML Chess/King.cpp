
#include "King.h"
#include<iostream>
#include"Rook.h"
#include"Board.h"
#include"Utility.h"
#include <Windows.h>

using namespace std;

King::King(Position p, pColor c, Board* b) : Piece(p, c, b) {
    isFirstMove = false;
}

//void King::drawPiece(Position center) {
//    gotoRowCol(center.rpos, center.cpos);
//    std::cout << ((clr == White) ? 'K' : 'k');
//}



bool King::legalMove(Board* B, Position S, Position D) {
    if (S.rpos == D.rpos && S.cpos == D.cpos)
        return false;
    int r1 = S.rpos;
    int c1 = S.cpos;
    int r2 = D.rpos;
    int c2 = D.cpos;
    if (r1 == r2 && c1 == c2)
        return false;
    // Check if the move is valid
    if ((r2 == r1 - 1 || r2 == r1 + 1 || r2 == r1) &&
        (c2 == c1 - 1 || c2 == c1 + 1 || c2 == c1)) {
        B->enableCastling = false;
        return true;
    }
    else if (r1 == r2 && abs(c2 - c1) == 2 && !isFirstMove) {
        // Check for castling legality
        int direction = (c2 - c1) / abs(c2 - c1);
        Position rookPos(r1, (direction == 1) ? 7 : 0);
        Piece* rook = B->getPiece(rookPos);
        if (rook != nullptr && rook->getType() == ROOK && !rook->FirstMove())
        {
            if (!HorizentalPathclear(S, D))
                return false;
            // The castling move is legal
            B->enableCastling = true;
            return true;
        }
    }
    B->enableCastling = false;
    return false;
}


#define SQUARE_SIZE 9
//void King::drawPiece(Position center) {
//    int x = center.cpos + 1; //* SQUARE_SIZE + SQUARE_SIZE / 2;
//    int y = center.rpos + 1;//* SQUARE_SIZE + SQUARE_SIZE / 2;
//    char symbol = char(-37);
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
//    // Draw horizontal line
//    for (int i = x - SQUARE_SIZE / 4; i <= x + SQUARE_SIZE / 4; i++) {
//        std::cout << "\033[" << y << ";" << i << "H" << symbol;
//    }
//
//    // Draw vertical line
//    for (int i = y - SQUARE_SIZE / 4; i <= y + SQUARE_SIZE / 4; i++) {
//        std::cout << "\033[" << i << ";" << x << "H" << symbol;
//    }
//    SetClr(WHITE, BLACK);
//}

void King::drawPiece(sf::RenderWindow& window, sf::Vector2f center) {
    sf::Texture texture;
    if (clr == White)
    {
        if (!texture.loadFromFile("images\\white-king.png")) {
            // Failed to load image
            return;
        }
    }
    else
    {
        if (!texture.loadFromFile("images\\black-king.png")) {
            // Failed to load image
            return;
        }
    }
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(center);

    window.draw(sprite);
}
void King::move(Position P)
{
    isFirstMove = true;
    Piece::move(P);
}
bool King::FirstMove()
{
    return isFirstMove;
}
PieceType King::getType()
{
    return KING;
}