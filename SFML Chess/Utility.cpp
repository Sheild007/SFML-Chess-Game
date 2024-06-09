#include"Utility.h"
#include"Position.h"
#include<iostream>
#include<Windows.h>
using namespace std;


//void getRowColbyLeftClick(int& rpos, int& cpos)
//{
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	DWORD Events;
//	INPUT_RECORD InputRecord;
//	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
//	do
//	{
//		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
//		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//		{
//			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
//			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
//			break;
//		}
//	} while (true);
//}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void L2R(sf::RenderWindow& window, int r, int cs, int ce, char sym, sf::Color clr)
{
    
    sf::RectangleShape line(sf::Vector2f(1, 10));
    line.setFillColor(clr);

    for (int c = cs; c <= ce; c++)
    {
        line.setPosition(sf::Vector2f(c, r));
        window.draw(line);
        window.display();
    }
}
void T2B(sf::RenderWindow& window, int r, int cs, int ce, char sym, sf::Color clr)
{
    sf::RectangleShape line(sf::Vector2f(10, 1));
    line.setFillColor(clr);

    for (int c = cs; c <= ce; c++)
    {
        line.setPosition(sf::Vector2f(r, c));
        window.draw(line);
    }
}

void drawBox(sf::RenderWindow& window, int r, int c, int boxSize, sf::Color clr,int shift,int shift2)
{
    sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
    box.setFillColor(clr);

    box.setPosition(c * boxSize+shift, r * boxSize+shift2);

    window.draw(box);
}

void drawBoard(sf::RenderWindow& window, int numRows, int numCols, int boxSize,int shift,int shift2)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            sf::Color clr;
            if ((i + j) % 2 == 0)
            {
                // Use brown color for even squares
                clr = sf::Color(50, 50, 50,80);
               // float grayscale = 0.5f;
                //clr = sf::Color(grayscale, grayscale, grayscale);
                //clr = Color::Black;
            }
            else
            {
                // Use yellow color for odd squares
               // clr = sf::Color(255, 255, 153);
                clr = Color::White;
            }
            drawBox(window, i, j, boxSize, clr,shift,shift2);
        }
    }
}
void RemovePieces(sf::RenderWindow& window, int boxdim, Position Sc, Position Dc)
{
    sf::Color clr = ((Sc.rpos + Sc.cpos) % 2 == 0) ? sf::Color(139, 69, 19) : sf::Color(255, 255, 153);
   // drawBox(window, Sc.rpos * boxdim, Sc.cpos * boxdim, boxdim, clr,);
  

    if (Dc.rpos != -1)
    {
        sf::Color clr = ((Sc.rpos + Sc.cpos) % 2 == 0) ? sf::Color(139, 69, 19) : sf::Color(255, 255, 153);
      //  drawBox(window, Dc.rpos * boxdim, Dc.cpos * boxdim, boxdim,clr);
    }
}
void UnHighlight(sf::RenderWindow& window, int dim, int rows, int cols, bool** Map)
{
    int clr;
    int shift = rows - 1;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (Map[i][j] == true)
            {
                sf::Color clr = ((i + j) % 2 == 0) ? sf::Color(211, 211, 211) : sf::Color(128, 128, 128);
                L2R(window, i * rows, j * cols, ((j + 1) * cols) - 1, -37, clr);
                L2R(window, i * rows + shift, j * cols, ((j + 1) * cols) - 1, -37, clr);
                int c = j * cols;
                T2B(window, c, i * rows, ((i + 1) * rows) - 1, -37, clr);
                T2B(window, c + shift, i * rows, ((i + 1) * rows) - 1, -37, clr);
            }
        }
    }
}
void Highlight(sf::RenderWindow& window, int dim, int rows, int cols, bool** Map,int shiftc,int shiftr)
{
    int radius = 7;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(0, 255, 0));
    circle.setOutlineThickness(2.0f);
    circle.setOutlineColor(sf::Color::Black);

    int shift = rows - 1;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (Map[i][j] == true)
            {
                int x = j * cols + cols / 2+shiftc;
                int y = i * rows + rows / 2+shiftr;

                circle.setPosition(x - radius, y - radius);
                window.draw(circle);
              
            }
        }
    }
}

void  getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window)
{
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i p = sf::Mouse::getPosition(window);

			cpos = p.x;
			rpos = p.y;
			break;
		}
	}
}
