#pragma once
#include<Siv3D.hpp>
#include"MRBallet.hpp"
#include"MREnemy.hpp"

class MREntityManager{
public:

	static MREntityManager* GetInstance()
	{
		static MREntityManager instance;
		return &instance;
		//some
	}

	MREntityManager(const MREntityManager& rhs) = delete;

	MREntityManager& operator=(const MREntityManager& rhs) = delete;

	void createBallet(const std::shared_ptr<MRBallet>& b)
	{
		balletList.push_back(b);
	}

	void createEnemy(const std::shared_ptr<MREnemy>& e)
	{
		enemyList.push_back(e);
	}

	void update()
	{
		collision();

		for (auto& b : balletList)
		{
			b->move();
		}

		for (auto& e : enemyList)
		{
			e->move();
		}

		Erase_if(balletList, [](const std::shared_ptr<MRBallet>& b){ return b->isDead(); });
		Erase_if(enemyList, [](const std::shared_ptr<MREnemy>& e){ return e->isDead(); });

	}

	void draw()const
	{
		for (const auto& b : balletList)
		{
			b->draw();
		}

		for (const auto& e : enemyList)
		{
			e->draw();
		}

		Circle(50, 50, 50).draw(Palette::Black);

		FontAsset(L"Score")(score).drawCenter({50, 50},Palette::Red);

	}

	void collision()
	{
		Erase_if(balletList, [=](const std::shared_ptr<MRBallet>& b)
		{
			if (AnyOf(enemyList, [b](const std::shared_ptr<MREnemy>& e){ return (e->getPos().distanceFrom(b->getPos()) < 20); }))
			{
				++score;
				return true;
			}
			else return false;
		});
	}

	//追尾弾用に敵キャラクタの位置を提供する
	Point getChasedEnemyPoint()const
	{
		//選択アルゴリズム：ランダム 敵がいなければ特定の座標を返す
		const size_t size = enemyList.size();

		if (size == 0) return Point(320,160);

		const int targetIndex = Random<int>(0, size-1);

		return enemyList[targetIndex]->getPos();
	}

	int getScore()const
	{
		return score;
	}


private:

	MREntityManager() : score(0)
	{
	}

	int score;

	std::vector<std::shared_ptr<MRBallet> > balletList;

	std::vector<std::shared_ptr<MREnemy> > enemyList;


};