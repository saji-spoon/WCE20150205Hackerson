#pragma once
#include<Siv3D.hpp>

class MREntity
{
public:

	MREntity(){}

	MREntity(const Point& p) :pos(p)
	{}

	virtual void draw()const = 0;

	virtual void move() = 0;

	//オブジェクトを削除してよい状態かどうか
	virtual bool isDead()
	{
		return !Window::ClientRect().intersects(pos);//デフォルトは画面から出た時
	}


protected:

	Point pos;

};