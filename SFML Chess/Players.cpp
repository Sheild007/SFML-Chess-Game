#include"Utility.h"
#include "Players.h"

Players::Players(string N, pColor c)
{
	Name = N;
	clr = c;
}

Players::Players()
{
	Name = "";
	clr;
}

string Players::getName()
{
	return Name;
}

pColor Players::getColor()
{
	return clr;
}
void Players::SetName(string N)
{
	Name = N;
}

Players& Players::operator=(const Players& others)
{
	if (this != &others) {
		Name = others.Name;
		clr = others.clr;
	}
	return *this;
}
void Players::setColor(pColor c)
{
	clr = c;

}