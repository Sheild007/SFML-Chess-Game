

#ifndef UTILITY_H
#define UTILITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
using namespace sf;
#include<windows.h>
#include<string>
#include"Position.h"
#include<string>
using namespace std;

enum pColor { White, Black };
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };




#define LightGrey 7
#define Grey 8
#define WHITE 15
#define BLACK 0
#define Red 12
#define Blue 9

//void getRowColbyLeftClick(int& rpos, int& cpos);
void getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window);
void gotoRowCol(int rpos, int cpos);
void SetClr(int tcl, int bcl);
void L2R(sf::RenderWindow& window, int r, int cs, int ce, char sym, sf::Color clr);
void T2B(sf::RenderWindow& window, int r, int cs, int ce, char sym, sf::Color clr);
void drawBox(sf::RenderWindow& window, int r, int c, int boxSize, sf::Color clr,int,int);
void drawBoard(sf::RenderWindow& window, int numRows, int numCols, int boxSize,int,int);
void RemovePieces(sf::RenderWindow& window, int boxdim, Position Sc, Position Dc);
void UnHighlight(sf::RenderWindow& window, int dim, int rows, int cols, bool** Map);
void Highlight(sf::RenderWindow& window, int dim, int rows, int cols, bool** Map,int,int);

#endif