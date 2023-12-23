#pragma once
#ifndef __Carrot__MoveControllerBase_h
#define __Carrot__MoveControllerBase_h

#include "MonsterBase.h"

class MoveControllerBase : public Node
{
	friend class MonsterBase;
public:

	virtual ~MoveControllerBase();
	
	virtual void ListenerMonster(float t);//���ƹ��ﶯ��


private:
	
	void SetMonster(MonsterBase* Momster); //�����ƶ��Ĺ���
	
	void ErasePoint();//ɾ��·���еĵ�

	virtual bool Init(MonsterBase* Momster);//��ʼ��

	static MoveControllerBase* Create(MonsterBase* Momster);//���� MoveControllerBase ��ʵ��

	CC_SYNTHESIZE_PASS_BY_REF(int, myMonsterSpeed, MyMonsterSpeed);

	Animation* AnimationMaker(int BulletType, float t);//���ﶯ������

	MoveControllerBase() {}
private:

	MonsterBase* pMonster = nullptr;

	std::vector<Vec2>* pMapPonits;//�洢�����ƶ���·����

};
#endif
