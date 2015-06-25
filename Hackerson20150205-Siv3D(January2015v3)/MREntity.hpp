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

	//�I�u�W�F�N�g���폜���Ă悢��Ԃ��ǂ���
	virtual bool isDead()
	{
		return !Window::ClientRect().intersects(pos);//�f�t�H���g�͉�ʂ���o����
	}


protected:

	Point pos;

};