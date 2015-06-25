#pragma once
#include<Siv3D.hpp>
#include"MRBallet.hpp"

class MRBalletManager{
public:
	
	static MRBalletManager* GetInstance()
	{
		static MRBalletManager instance;
		return &instance;
	}

	MRBalletManager(const MRBalletManager& rhs) = delete;

	MRBalletManager& operator=(const MRBalletManager& rhs) = delete;

	void create(std::shared_ptr<MRBallet> b)
	{
		balletList.push_back(b);
	}

	void update()
	{
		auto it = balletList.begin();

		while (it != balletList.end()) {
			if ( !it->get()->isDead() ) {
				it = balletList.erase(it);
			}
			else
			{
				(*it)->move();

				++it;
			}
		}
	}

	void draw()const
	{
		for (const auto& b : balletList)
		{
			b->draw();
		}

		
	}

private:
	
	MRBalletManager(){}

	std::vector<std::shared_ptr<MRBallet> > balletList;

	
};