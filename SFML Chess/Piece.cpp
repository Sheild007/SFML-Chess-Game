
#include "Piece.h"
#include<math.h>
#include"Board.h"
#include"Position.h"
#include"Utility.h"


Piece::Piece(Position p, pColor c, Board* b)
{
    pos = p;
    clr = c;
    B = b;

}

void Piece::move(Position P)
{

    pos = P;
}
pColor Piece::getColor()
{

    return clr;
}

bool Piece::isHorizontalMove(Position Sc, Position Dc)
{
    return(Sc.rpos == Dc.rpos);

}
bool Piece::isVerticalMove(Position Sc, Position Dc)
{
    return(Sc.cpos == Dc.cpos);
}
bool Piece::isDiagonalMove(Position Sc, Position Dc)
{
    return (abs(Sc.rpos - Dc.rpos) == abs(Sc.cpos - Dc.cpos));
}
bool Piece::isMainDiagonalMove(Position Sc, Position Dc)
{
    return ((Sc.rpos - Dc.rpos) == (Sc.cpos - Dc.cpos));
}
bool Piece::isSecDiagonalMove(Position Sc, Position Dc)
{
    return (abs(Sc.rpos - Dc.rpos) == abs(Sc.cpos - Dc.cpos) && (Sc.rpos - Dc.rpos) != (Sc.cpos - Dc.cpos));
}
// Check if the vertical path is clear from Sc to Dc
bool  Piece::verticalPathclear(Position Sc, Position Dc)
{
    int startRow = min(Sc.rpos, Dc.rpos);
    int endRow = max(Sc.rpos, Dc.rpos);
    int col = Sc.cpos;
    for (int i = startRow + 1; i < endRow; i++) {
        if (B->getPiece(Position(i, col)) != NULL)
        {
            return false;
        }
    }
    return true;
}


// Check if the horizontal path is clear from Sc to Dc
bool  Piece::HorizentalPathclear(Position Sc, Position Dc) {
    int startCol = min(Sc.cpos, Dc.cpos);
    int endCol = max(Sc.cpos, Dc.cpos);
    int row = Sc.rpos;
    for (int i = startCol + 1; i < endCol; i++) {
        if (B->getPiece(Position(row, i)) != NULL) {
            return false;
        }
    }
    return true;
}

// Check if the diagonal path is clear from Sc to Dc
bool Piece::DignalPathclear(Position Sc, Position Dc) {
    int rowDiff = abs(Dc.rpos - Sc.rpos);
    int colDiff = abs(Dc.cpos - Sc.cpos);
    if (rowDiff != colDiff) {
        return false;
    }
    int rowInc = (Dc.rpos > Sc.rpos) ? 1 : -1;
    int colInc = (Dc.cpos > Sc.cpos) ? 1 : -1;
    int row = Sc.rpos + rowInc;
    int col = Sc.cpos + colInc;
    while (row != Dc.rpos && col != Dc.cpos) {
        if (B->getPiece(Position(row, col)) != NULL) {
            return false;
        }
        row += rowInc;
        col += colInc;
    }
    return true;
}
bool Piece::isMyPiece(Position P, int turn)
{
    if (B->getPiece(P) == nullptr)
        return false;
    return (turn == B->getPiece(P)->getColor());

}
bool** Piece::HighlightLoc(Board* board, Position Sc, int turn)
{
    bool** boolB = new bool* [8]{};
    for (int i = 0; i < 8; i++)
    {
        boolB[i] = new bool[8]{};
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Position dc;
            dc.rpos = i; dc.cpos = j;
            if (!isMyPiece(dc, turn))
            {

                boolB[i][j] = legalMove(board, Sc, dc);
            }

        }
    }
    return boolB;
}

//bool Piece::isMyPiece(int turn)
//{
//    // Check if the piece exists and has the correct color
//    return (this != nullptr && p->getColor() == turn);
//    
//}



