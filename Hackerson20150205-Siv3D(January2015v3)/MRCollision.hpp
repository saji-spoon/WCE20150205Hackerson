#pragma once
#include<Siv3D.hpp>
#include"MREnemyManager.hpp"
#include"MRBalletManager.hpp"


class MRCollision
{
public:

	MRCollision(){}

	void update()
	{
		MREnemyManager::GetInstance();
		MRBalletManager::GetInstance();
	}

private:

};