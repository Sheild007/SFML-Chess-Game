#include"Position.h"

Position::Position()
{
	rpos = 0;
	cpos = 0;
}

Position::Position(int r, int c)
{
	rpos = r;
	cpos = c;
}
Position& Position:: operator=(const Position& other)
{
	if (this != &other)
	{
		rpos = other.rpos;
		cpos = other.cpos;

	}
	return *this;
}