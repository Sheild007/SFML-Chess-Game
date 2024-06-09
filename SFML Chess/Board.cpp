
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string>
using namespace sf;
#include<iostream>
using namespace std;

#include"Utility.h"
#include "Board.h"
#include<iostream>
#include<cstring>
#include"Bishop.h"
#include"King.h"
#include"Knight.h"
#include"Pawn.h"
#include"Queen.h"
#include"Rook.h"
#include "Piece.h"
#include "Players.h"
#include"Position.h"
#include<fstream>

using namespace std;


#define X 702.0f
#define Y 75.0f
// Spacing between the pieces
#define spacing 51.0f
// Background board color
#define boardColor Color(150,100,45,255)

Board::Board()
{
	rows = 0;
	cols = 0;
	Bdim = 0;
	enableCastling = false;
}
Board::Board(int b)
{
	rows = 8;
	cols = 8;
	Bdim = b;
	enableCastling = false;
	allocate();
	init();
}
void Board::load(ifstream& read)
{
	allocate();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			char c;
			read >> c;
			Position pos(i, j);
			switch (c)
			{
			case '-':
				Ps[i][j] = nullptr;
				break;
			case 'p':

				Ps[i][j] = new Pawn(pos, Black, this);
				break;
			case 'P':
				Ps[i][j] = new Pawn(pos, White, this);
				break;
			case 'k':
				Ps[i][j] = new King(pos, Black, this);
				break;
			case 'K':
				Ps[i][j] = new King(pos, White, this);
				break;
			case 'q':
				Ps[i][j] = new Queen(pos, Black, this);
				break;
			case 'Q':
				Ps[i][j] = new Queen(pos, White, this);
				break;
			case 'r':
				Ps[i][j] = new Rook(pos, Black, this);
				break;
			case 'R':
				Ps[i][j] = new Rook(pos, White, this);
				break;
			case 'n':
				Ps[i][j] = new Knight(pos, Black, this);
				break;
			case 'N':
				Ps[i][j] = new Knight(pos, White, this);;
				break;
			case 'b':
				Ps[i][j] = new Bishop(pos, Black, this);
				break;
			case 'B':
				Ps[i][j] = new Bishop(pos, White, this);
				break;
			default:

				break;
			}
		}
	}
}
Board::Board(const Board& other) {

	copy(other);

}
void Board::copy(const Board& other)
{


	// Copy the size of the board
	this->Bdim = other.Bdim;
	this->cols = other.cols;
	this->enableCastling = other.enableCastling;
	this->rows = other.rows;

	// Allocate memory for the new Ps array
	allocate();

	// Copy the pieces from the other board
	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			// Check if there is a piece on the other board
			Piece* p = other.getPiece(Position(r, c));
			if (p != nullptr) {
				// Create a new piece of the same type and pColor
				Piece* newPiece;
				Position pos(r, c);
				if (dynamic_cast<Pawn*>(p))
				{
					newPiece = new Pawn(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else if (dynamic_cast<Knight*>(p)) {
					newPiece = new Knight(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else if (dynamic_cast<Bishop*>(p)) {
					newPiece = new Bishop(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else if (dynamic_cast<Rook*>(p)) {
					newPiece = new Rook(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else if (dynamic_cast<Queen*>(p)) {
					newPiece = new Queen(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else if (dynamic_cast<King*>(p)) {
					newPiece = new King(pos, p->getColor(), this);
					Ps[r][c] = newPiece;
				}
				else {
					// Should never happen
					newPiece = nullptr;
					Ps[r][c] = newPiece;
				}

			}

		}
	}
}

void Board::allocate()
{
	Ps = new Piece * *[rows];
	for (int i = 0; i < rows; i++) {
		Ps[i] = new Piece * [cols] {};
	}
}
void Board::init()
{
	//create and place the pieces
	for (int i = 0; i < cols; i++)
	{

		Ps[1][i] = new Pawn(Position(1, i), Black, this);
		Ps[6][i] = new Pawn(Position(6, i), White, this);
		int check = Ps[6][0]->getColor();

	}

	Ps[0][0] = new Rook(Position(0, 0), Black, this);
	Ps[0][7] = new Rook(Position(0, 7), Black, this);
	Ps[7][0] = new Rook(Position(7, 0), White, this);
	Ps[7][7] = new Rook(Position(7, 7), White, this);

	Ps[0][1] = new Knight(Position(0, 1), Black, this);
	Ps[0][6] = new Knight(Position(0, 6), Black, this);
	Ps[7][1] = new Knight(Position(7, 1), White, this);
	Ps[7][6] = new Knight(Position(7, 6), White, this);

	Ps[0][2] = new Bishop(Position(0, 2), Black, this);
	Ps[0][5] = new Bishop(Position(0, 5), Black, this);
	Ps[7][2] = new Bishop(Position(7, 2), White, this);
	Ps[7][5] = new Bishop(Position(7, 5), White, this);

	Ps[0][3] = new Queen(Position(0, 3), Black, this);
	Ps[7][3] = new Queen(Position(7, 3), White, this);

	Ps[0][4] = new King(Position(0, 4), Black, this);
	Ps[7][4] = new King(Position(7, 4), White, this);
}
Piece* Board::getPiece(Position P) const
{
	return Ps[P.rpos][P.cpos];
}
void Board::printBoard(sf::RenderWindow&win,int boxSize,int shift1,int shift2)
{

	int fixR = 0;
	int fixC = 0;
	Position center;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			
			Vector2f cen;
			cen.y = i + boxSize / 2 + fixR+shift2, cen.x= j + boxSize / 2 + fixC+shift1;
			
			if (Ps[i][j] != nullptr)
				Ps[i][j]->drawPiece(win,cen);


			fixC += (boxSize - 1);

		}
		fixC = 0;
		fixR += (boxSize - 1);

	}

}

void Board::selectPosition(Position& P,RenderWindow& win)
{
	int x, y;
	getRowColbyLeftClick(x, y, win);
	P.rpos = x/50 ;
	P.cpos = y/50;

}
bool validRange(Position P)
{
	if (P.rpos < 0 || P.rpos>=8 || P.cpos < 0 || P.cpos>=8)
		return false;
	return true;
}
void Board::removePiece(Position pos)
{
	Ps[pos.rpos][pos.cpos] = nullptr;
}
void Board::placePiece(Piece* P, Position pos)
{
	Ps[pos.rpos][pos.cpos] = P;

}
bool Board::isValidSource(Position P, int turn)
{
	if (!validRange(P))
		return false;
	if (Ps[P.rpos][P.cpos] == NULL)
		return false;
	else if (turn != Ps[P.rpos][P.cpos]->getColor())
		return false;
	
	return true;
}
bool Board::isValidDest(Position P, int turn)
{
	if (!validRange(P))
		return false;
	if (Ps[P.rpos][P.cpos] == NULL)
		return true;
	else if (turn == Ps[P.rpos][P.cpos]->getColor())
		return false;
	return true;
}
void Board::changeTurn(int& Turn)
{
	Turn = (Turn + 1) % 2;
}
void Board::TurnMessage(Players* P)
{

	gotoRowCol(8 * Bdim + 1, 2);
	cout << "                              ";
	gotoRowCol(8 * Bdim + 1, 2);
	cout << P->getName() << "'s Turn" << endl;
}
void Board::movePiece(Position S, Position D)
{
	Ps[D.rpos][D.cpos] = Ps[S.rpos][S.cpos];
	Ps[S.rpos][S.cpos] = nullptr;

}
void Board::DrawOnePiece(Position D)
{
	int fixR = D.rpos * (Bdim - 1);
	int fixC = D.cpos * (Bdim - 1);
	Position center;
	center.rpos = D.rpos + Bdim / 2 + fixR, center.cpos = D.cpos + Bdim / 2 + fixC;
	if (Ps[D.rpos][D.cpos] != nullptr);
		//Ps[D.rpos][D.cpos]->drawPiece(center);
}
Position Board::findKing(int turn)
{
	// Iterate through each square on the board
	for (int r = 0; r < 8; ++r)
	{
		for (int c = 0; c < 8; ++c)
		{
			Piece* p = Ps[r][c];
			// If the square is occupied by a king of the specified pColor, return its position
			if (p != nullptr && p->getType() == KING && p->getColor() == turn)
			{
				return { r, c };
			}
		}
	}
	// If the king isn't found, return an invalid position
	return { -1, -1 };
}
bool Board::check(int turn)
{
	Position Sc;
	changeTurn(turn);
	Position Dc = findKing(turn);
	changeTurn(turn);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Sc.rpos = i, Sc.cpos = j;
			if ((Ps[Sc.rpos][Sc.cpos]) != nullptr && Ps[Sc.rpos][Sc.cpos]->getColor() == turn)
			{
				if (Ps[Sc.rpos][Sc.cpos]->legalMove(this, Sc, Dc))
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool Board::selfCheck(int turn)
{

	changeTurn(turn);
	return check(turn);

}

bool Board::checkmate(int turn)
{
	Position MyPiece, Dc, prev;
	bool checkmate = true; // initialize to true

	Board* copy = this->clone();
	changeTurn(turn);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			prev.rpos = i, prev.cpos = j;
			MyPiece.rpos = i, MyPiece.cpos = j;
			if (Ps[i][j] != nullptr && Ps[i][j]->getColor() == turn)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						Dc.rpos = k, Dc.cpos = l;
						if (Ps[MyPiece.rpos][MyPiece.cpos]->legalMove(this, MyPiece, Dc))
						{
							copy->movePiece(prev, Dc);
							if (!copy->selfCheck(turn))
							{
								// return false immediately if a legal move is found
								return false;
							}
							prev = Dc; // set prev to current destination position
						}
					}
				}
				prev.rpos = i, prev.cpos = j; // reset prev to initial value
			}
		}
	}
	// changeTurn effects should be reversed if necessary
	return checkmate;
}

//bool Board::stalemate(int turn)
//{
//	// Check if the current player is in check
//	if (check(turn))
//	{
//		return false;
//	}
//
//	// Iterate through each of the player's pieces
//	Board copy = *this;
//	changeTurn(turn);
//	for (int r = 0; r < 8; ++r) {
//		for (int c = 0; c < 8; ++c) {
//			Piece* p = Ps[r][c];
//			Position src(r, c);
//			// Check if the piece is of the current player's pColor
//			if (p != nullptr && p->getColor() == turn) {
//				// Iterate through each square on the board
//				for (int i = 0; i < 8; ++i) {
//					for (int j = 0; j < 8; ++j) {
//						Position dst(i, j);
//						// Check if the piece can legally move to the square
//						if (p->legalMove(this, src, dst))
//						{
//
//							// Make a copy of the board and move the piece
//							
//							copy.movePiece(src, dst);
//							// Check if the move results in the player being in check
//							if (copy.check(turn)) {
//								return false;
//							}
//						
//							copy = *this;
//						
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// If none of the player's pieces can legally move without resulting in a check, it's a stalemate
//	return true;
//}


//bool Board::stalemate(int turn)
//{
//	Position MyPiece, Dc, prev;
//	// Check if the current player is in check
//	if (check(turn))
//	{
//		return false;
//	}
//
//	// Create a single copy of the board to be used for checking moves
//	Board* copy = this->clone();
//	
//	// Iterate through each of the player's pieces
//	
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			prev.rpos = i, prev.cpos = j;
//			MyPiece.rpos = i, MyPiece.cpos = j;
//			if (Ps[i][j] != nullptr && Ps[i][j]->getColor() != turn)
//			{
//				for (int k = 0; k < 8; k++)
//				{
//					for (int l = 0; l < 8; l++)
//					{
//						Dc.rpos = k, Dc.cpos = l;
//						if (Ps[MyPiece.rpos][MyPiece.cpos]->legalMove(this, MyPiece, Dc))
//						{
//							copy->movePiece(prev, Dc);
//							if (selfCheck(turn))
//							{
//								// return false immediately if a legal move is found
//								return false;
//							}
//							prev = Dc; // set prev to current destination position
//						}
//					}
//				}
//				prev.rpos = i, prev.cpos = j; // reset prev to initial value
//			}
//		}
//	}
//	// Delete the copy board
//	delete copy;
//
//	// If none of the player's pieces can legally move without resulting in a check, it's a stalemate
//	return true;
//}
bool Board::stalemate(int turn)
{
	// Check if the current player is in check
	if (check(turn))
	{
		return false;
	}

	// Create a single copy of the board to be used for checking moves
	Board* copy = this->clone();

	// Iterate through each of the player's pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Ps[i][j] != nullptr && Ps[i][j]->getColor() != turn)
			{
				// Iterate over each possible move for the piece
				Position src(i, j);
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						Position dst(k, l);
						if (Ps[i][j]->legalMove(this, src, dst))
						{
							// Make a copy of the board and try the move
							Board* copy = this->clone();
							copy->movePiece(src, dst);

							// Check if the move results in the player being in check
							bool isCheck = copy->check(turn);

							// Delete the copy board
							delete copy;

							if (!isCheck)
							{
								// If the move does not result in the player being in check, it's not a stalemate
								return false;
							}
						}
					}
				}
			}
		}
	}

	// If none of the player's pieces can legally move without resulting in a check, it's a stalemate
	return true;
}
void Board::promote(int choice, Position pos, pColor pColor)
{
	Piece* newPiece;
	switch (choice) {
	case 1:
		newPiece = new Queen(pos, pColor, this);
		break;
	case 2:
		newPiece = new Rook(pos, pColor, this);
		break;
	case 3:
		newPiece = new Bishop(pos, pColor, this);
		break;
	case 4:
		newPiece = new Knight(pos, pColor, this);
		break;
	default:
		std::cout << "Invalid choice.\n";
		return;
	}
	Ps[pos.rpos][pos.cpos] = newPiece;
}

Board* Board::clone() {
	Board* newBoard = new Board(*this); // use copy constructor to create new board object
	return newBoard;
}

Board& Board::operator= (const Board& other) {
	// Check for self-assignment
	if (this == &other) {
		return *this;
	}
	/**

	sf::RenderWindow window(sf::VideoMode().getdesktopMode(),"Chess",sf::Style::Default);
	sf::E
	while (window.isopen())
	{
		sf::Event::Mouse







		////
		window.clear();

		window.drwa();


		window.display();




	}
	*/






	// Copy the other board to this board

	this->copy(other);

	return *this;
}
void Board::clearBoard() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			Ps[r][c] = nullptr;
		}
		delete[] Ps[r];
		Ps[r] = nullptr;
	}
	delete[] Ps;
	Ps = nullptr;

}

void Board::setPiece(Piece* piece, const Position& position) {
	// Get the row and column indices from the position
	int row = position.rpos;
	int col = position.cpos;

	// Set the piece at the specified position
	Ps[row][col] = piece;
}




