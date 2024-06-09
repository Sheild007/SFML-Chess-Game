#ifndef POSITION_H
#define POSITION_H
class Position
{
public:
	int rpos;
	int cpos;
	Position();
	Position(int r, int c);
	Position& operator=(const Position& other);
};

#endif