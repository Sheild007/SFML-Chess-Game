#ifndef PLAYERS_H
#define PLAYERS_H

#include<string>
#include"Utility.h"

using namespace std;

class Players
{
	string Name;
	pColor clr;

public:
	Players();
	Players(string Name, pColor clr);
	string getName();
	pColor getColor();
	void SetName(string N);
	void setColor(pColor c);
	Players& operator=(const Players& others);

};
#endif
