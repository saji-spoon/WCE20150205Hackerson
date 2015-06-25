#pragma once
#include<Siv3D.hpp>
#include"MREntity.hpp"

class MREnemy : public MREntity
{
public:

	MREnemy(){}

	MREnemy(const Point& p, const Point& v = {0.0, 0.0}) :MREntity(p), velocity(v){}

	void draw()const override
	{
		Rect(pos - Point(30, 30), { 60, 60 })(TextureAsset(L"oni")).draw();;
	}

	virtual void move() override
	{
		pos += velocity;
	}

	Point getPos()const
	{
		return pos;
	}

	inline bool isDead()override
	{
		return !Window::ClientRect().stretched(50).intersects(pos);//デフォルトは画面から出た時
	}


protected:

	Point velocity;
};

//往復をｘ方向に何度かする敵
class MREnemyRound : public MREnemy
{
public:

	MREnemyRound(const Point& p, const Point& v = { 0, 0 }, int bc = 3) :MREnemy(p,v),boundCount(bc){}


	void move() override
	{
		pos += velocity;
		
		if (((Rect(Point(540, 0), Point(20, 480)).intersects(pos) && velocity.x>0) ||
			(Rect(Point(100, 0), Point(20, 480)).intersects(pos) && velocity.x<0)) &&
			boundCount > 0)
		{
			velocity.x *= -1;
			--boundCount;
		}
		
		
	}

	Point getPos()const
	{
		return pos;
	}

private:

	int boundCount;

};

class MREnemyStop : public MREnemy
{
public:

	MREnemyStop(){}

	MREnemyStop(const Point& p, unsigned int ls) :MREnemy(p), lifeSpan(ls), awaken(false){ }

	void move()override
	{
		if (awaken) return;

		awaken = true;

		timer.restart();
	}

	inline bool isDead()override
	{
		return (timer.elapsed() > lifeSpan);//寿命をこえた
	}


protected:

	Point velocity;

	unsigned int lifeSpan;

	TimerSec timer;

	bool awaken;
};