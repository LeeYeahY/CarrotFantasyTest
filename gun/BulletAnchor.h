#pragma once
#include "BulletBase.h"
class BulletAnchor :public BulletBase
{

	friend class TowerAnchor;

protected:
	void DoAction();//ִ���ӵ��Ķ���
	void DoMove()override;//�����ӵ����ƶ�����
	virtual bool Init(const int& Id, VictimEntityBase* VictimEntity);//��ʼ��
	static BulletAnchor* Create(const int& Id, VictimEntityBase* VictimEntity);//����ʵ��

};
