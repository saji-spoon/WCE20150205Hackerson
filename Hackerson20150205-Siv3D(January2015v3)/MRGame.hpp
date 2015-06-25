#pragma once
#include<Siv3D.hpp>

class MRGame
{
public:

	MRGame(){}

	MRGame(const Point& p) :pos(p)
	{}

private:

	Point pos;

};