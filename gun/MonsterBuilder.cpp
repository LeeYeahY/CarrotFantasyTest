#include "MonsterBuilder.h"
#include "MapUtil.h"
#include "MonsterFactory.h"
#include "MonsterManager.h"
#include "LevelConfigUtil.h"
#include "MonsterBase.h"
#include "GameManager.h"
#include "SoundUtil.h"

bool MonsterBuilder::Init()
{
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!Node::init());//���Node��ʼ��ʧ�ܣ�������ѭ��
		myBuildNumber = 10;
		DelayTime = ConstDelayTime;
		MonsterCount = 0;
		MonsterBuilderNumber = 0;
		Delay = true;
		Number = 0;
		Batch = 0;
		GameManager::getInstance()->setMyMonsterBatch(0);//// ����Ϸ�������н�������������Ϊ0
		// ����������������֡�Ĺ��ﶯ��������������
		createMonsterAnimation = Animation::create();
		createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
		createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
		createMonsterAnimation->setDelayPerUnit(0.15);
		createMonsterAnimation->setLoops(1);
		createMonsterAnimation->retain();
		// �������ļ��ж�ȡ������������
		ReadFileMonsterCount = LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount();
		// ���ݵ�ͼ�еĵ�һ���ƶ�λ������MonsterBuilder��λ��
		this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));

		Ret = true;
	} while (0);
	return Ret;
}

void MonsterBuilder::OnEnter()
{
	Node::onEnter(); 
	schedule(schedule_selector(MonsterBuilder::CreateMonsterUpdate), 1.5, 20001, 3); // ����һ����ʱ����ÿ��1.5��ִ��һ�Σ��ظ�����Ϊ20001�����ܴ��ֵ���൱������ѭ���������ȼ�Ϊ3
}

void MonsterBuilder::CreateMonsterUpdate(float t)
{
	if (MonsterBuilderNumber == 10 * ReadFileMonsterCount)// ���MonsterBuilderNumber�ﵽ��һ��������������Ч��ȡ����ʱ����������֪ͨ����Ϸ�������
	{
		SoundUtil::getInstance()->playEffect(FINALWAVE);
		this->unschedule(schedule_selector(MonsterBuilder::CreateMonsterUpdate));
		NOTIFY->postNotification("openCheckGameEnd");
	}
	if (DelayTime < ConstDelayTime && MonsterManager::getInstance()->getMonsterVec().size() == 0)// ���DelayTimeС��ConstDelayTime������MonsterManager��û�й�����ڣ�������DelayTime
	{
		DelayTime += t;
	}
	else if (DelayTime >= ConstDelayTime)// ���DelayTime���ڵ���ConstDelayTime
	{
		Batch = MonsterBuilderNumber / 10 + 1;// ���㵱ǰ��������
		GameManager::getInstance()->setIMonsterBatch(Batch);// ����Ϸ�����������õ�ǰ��������
		NOTIFY->postNotification("monsterBatchChange", (Ref*)&Batch);// ���͹������α仯��֪ͨ
		MonsterFactoryController();// ���ù��﹤�����������ɹ���
		MonsterCount++;
		MonsterBuilderNumber++;
		if (MonsterCount == 10)// ���MonsterCount�ﵽ10������DelayTime��MonsterCount
		{
			DelayTime = 0;
			MonsterCount = 0;
		}
	}
}

void MonsterBuilder::MonsterFactoryController()
{
	SoundUtil::getInstance()->playEffect(BUILDMONSTER);
	if (Number == 10)Number = 0;// ���Number�ﵽ10������Ϊ0
	int number = 10 - (Batch - 1) * 2;// �������μ��㵱ǰ�������ɵĹ�����������
	MonsterBase* pMonster;
	if (Batch == ReadFileMonsterCount && Number == 5)// ��������ѡ��������ͨ�����Boss����
	{
		pMonster = MonsterFactory::CreateMonster(en_Boss_Big);
	}
	else
	{
		if (Number < number)// ����Number�ͼ���õ���number��ѡ�����ɲ�ͬ�������ͨ����
		{
			pMonster = MonsterFactory::CreateMonster(MonsterType(1 + int(Batch / 5)));
		}
		else
		{
			pMonster = MonsterFactory::CreateMonster(MonsterType(4 + int(Batch / 5)));
		}
	}
	pMonster->setMyHp(pMonster->getMyHp() + (Batch - 1) / 5 * pMonster->getMyHp());// �����������ù���ĳ�ʼѪ��������ٶ�
	pMonster->SetMaxSpeed(pMonster->getMySpeed() + int(Batch / 5) * 10);
	pMonster->getSprite()->runAction(Animate::create(createMonsterAnimation));// ���Ź������ɶ���
	Number++; //Number������׼��������һ������
}

int MonsterBuilder::GetBatch()
{
	return Batch;
}

MonsterBuilder::~MonsterBuilder()
{
	CC_SAFE_RELEASE_NULL(createMonsterAnimation);
}