#pragma once
#include<Siv3D.hpp>
#include"MREnemy.hpp"

class MREnemyManager{
public:

	static MREnemyManager* GetInstance()
	{
		static MREnemyManager instance;
		return &instance;
	}

	MREnemyManager(const MREnemyManager& rhs) = delete;

	MREnemyManager& operator=(const MREnemyManager& rhs) = delete;

	void create(const MREnemy& e)
	{
		enemyList.push_back(e);
	}

	void update()
	{
		std::vector<MREnemy>::iterator ite = enemyList.begin();

		while (ite != enemyList.end()) {
			if (!ite->isDead()) {
				ite = enemyList.erase(ite);
			}
			else
			{
				(*ite).move();

				++ite;
			}
		}
	}

	void draw()const
	{
		for (const auto& e : enemyList)
		{
			e.draw();
		}
	}


private:

	MREnemyManager(){}

	std::vector<MREnemy> enemyList;

};