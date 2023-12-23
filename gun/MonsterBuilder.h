#pragma once
#ifndef __Carrot__MonsterBuilder__
#define __Carrot__MonsterBuilder__
#include "cocos2d.h"
using namespace cocos2d;
class MonsterBuilder :public Node {

protected:

	virtual bool Init();

	float DelayTime;// �ӳ�ʱ��

	int MonsterCount;// ��������

	int MonsterBuilderNumber;// �������������

	int ReadFileMonsterCount;// ��ȡ���ļ���Ĺ�������

	bool Delay;// �Ƿ��ӳ����ɹ���

	const int ConstDelayTime = 8;// Ĭ���ӳ�ʱ��

	int Number;// ����

	int Batch; // ����

	virtual void OnEnter();

	void CreateMonsterUpdate(float t);// �������ɹ���ĺ���

	void MonsterFactoryController();// ���﹤�����ƺ���

	Animation* createMonsterAnimation; // ���ﶯ��

	~MonsterBuilder();

public:

	int GetBatch();// ��ȡ������

	CREATE_FUNC(MonsterBuilder);

	CC_SYNTHESIZE_PASS_BY_REF(int, myBuildNumber, MyBuildNumber);
};
#endif