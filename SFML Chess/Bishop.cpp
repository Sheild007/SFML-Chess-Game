
#include "Bishop.h"
#include<iostream>
#include<cmath>
#include"Position.h"
#include"Utility.h"
using namespace std;

#define X 702.0f
#define Y 75.0f
// Spacing between the pieces
#define spacing 51.0f

Bishop::Bishop(Position p, pColor c, Board* b) : Piece(p, c, b) {
	isFirstMove = false;
}
//void Bishop::drawPiece(Position center) 
//{
//	gotoRowCol(center.rpos, center.cpos);
//	std::cout << ((clr == White) ? 'B' : 'b');
//}
#define SQUARE_SIZE  9
//void Bishop::drawPiece(Position center) {
//	short x = center.cpos;
//	short y = center.rpos;
//	int fclr, bclr;
//	if (clr == White)
//		fclr = WHITE;
//	else
//		fclr = BLACK;
//	if ((center.rpos + center.cpos) % 2 == 0)
//		bclr = LightGrey
//		;
//	else
//		bclr = Grey;
//	SetClr(fclr, bclr);
//	char sym = -37;
//	char right = 221;
//	char left = 222;
//	gotoRowCol(center.rpos, center.cpos);
//	cout << sym;
//	gotoRowCol(center.rpos - 1, center.cpos - 1);
//	cout << sym;
//	gotoRowCol(center.rpos - 1, center.cpos + 1);
//	cout << sym;
//	SetClr(fclr, bclr);
//	gotoRowCol(center.rpos - 2, center.cpos - 1);
//	cout << sym;
//	gotoRowCol(center.rpos - 2, center.cpos + 1);
//	cout << sym;
//	gotoRowCol(center.rpos - 1, center.cpos - 2);
//	cout << sym;
//	gotoRowCol(center.rpos - 1, center.cpos + 2);
//	cout << sym;
//	gotoRowCol(center.rpos - 2, center.cpos - 2);
//	cout << left;
//	gotoRowCol(center.rpos - 2, center.cpos + 2);
//	cout << right;
//	gotoRowCol(center.rpos - 3, center.cpos - 1);
//	cout << sym;
//	SetClr(fclr, bclr);
//	gotoRowCol(center.rpos, center.cpos - 1);
//	cout << sym;
//	gotoRowCol(center.rpos, center.cpos + 1);
//	cout << sym;
//	SetClr(fclr, bclr);
//	L2R(center.rpos + 1, center.cpos - 2, center.cpos + 2, sym, fclr);
//
//	SetClr(WHITE, BLACK);
//}
void Bishop:: drawPiece(sf::RenderWindow& window, sf::Vector2f center) {
    sf::Texture texture;
    if (clr == White)
    {
        if (!texture.loadFromFile("images\\white-bishop.png")) {
            // Failed to load image
            return;
        }
    }
    else
    {
        if (!texture.loadFromFile("images\\black-bishop.png")) {
            // Failed to load image
            return;
        }
    }
    sf::Sprite sprite(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(center);

    window.draw(sprite);
}
void Bishop::move(Position P)
{
	isFirstMove = true;
	Piece::move(P);
}
bool Bishop::legalMove(Board* B, Position S, Position D)
{
	if (S.rpos == D.rpos && S.cpos == D.cpos)
		return false;
	return(isDiagonalMove(S, D) && DignalPathclear(S, D));
}

bool Bishop::FirstMove()
{
	return isFirstMove;
}
PieceType Bishop::getType()
{
	return BISHOP;
}