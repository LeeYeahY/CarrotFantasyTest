#include "BulletStar.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"

bool BulletStar::Init(const int& Id, VictimEntityBase* VictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::Init(Id, VictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletStar* BulletStar::Create(const int& Id, VictimEntityBase* VictimEntity)
{
	BulletStar* pBullet = new BulletStar();
	if (pBullet && pBullet->Init(Id, VictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletStar::DoAction()
{
	GetSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));//�������ӵ���ת360
}

void BulletStar::DoMove() {
	if (pAtkTarget->getIsDead())
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	DoAction();

	Animation* pAnimation = Animation::create();
	for (int i = 1; i < 7; i++)// ����ӵ��ķ��ж���֡
	{
		std::string SpriteFrameName = StringUtils::format("PStar-1%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	// ����֡�����Ĳ����ٶȺ�ѭ������
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);
	// ����һ���ص����������ڴ����ӵ�����Ŀ�����߼�
	auto deadActionCF = CallFunc::create([=]()
		{
			Rect rect = Rect(pAtkTarget->getPositionX() - 100, pAtkTarget->getPositionY() - 100, 200, 200);// ����һ�������������ڼ���ӵ��Ƿ����Ŀ��
			if (pAtkTarget->getAnimationFrameCount() != 0)// ���ݹ���Ŀ��Ķ���֡�����ж��ǹ��ﻹ���ϰ���,����ǹ���
			{
				Vector<MonsterBase*>  MonsterVector = Vector<MonsterBase*>(MonsterManager::getInstance()->GetMonsterVec());
				for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
				{
					MonsterBase* pMonster = (MonsterBase*)(*mIter);// ��ȡ��ǰ�������
					if (rect.intersectsRect(pMonster->getBoundingBox()))//��鵱ǰ����ı߽���Ƿ���ָ���ľ������� rect �ཻ
					{
						pMonster->Hurt(GetAtkProperty()); //������������					
					}
					if (pMonster->getMyHp() <= 0 || pMonster->getIsDead())//����Ƿ�����
					{
						MonsterVector.eraseObject(pMonster);
					}
					else
					{
						++mIter; //�������δ������������������������������һ������
					}
				}
			}
			else//���Ϊ�ϰ���
			{
				Vector<BarrierBase*>  BarrierVector = Vector<BarrierBase*>(BarrierManager::getInstance()->GetBarrierVec());
				for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
				{
					BarrierBase* pBarrier = (BarrierBase*)(*bIter);
					if (rect.intersectsRect(pBarrier->GetBoundingBox()))
					{
						pBarrier->Hurt(GetAtkProperty());
					}
					if (pBarrier->getMyHp() <= 0 || pBarrier->getIsDead())
					{
						/*bIter =*/ BarrierVector.eraseObject(pBarrier);
					}
					else
					{
						++bIter;
					}
				}
			}
			DeadMove(Name); // ִ���ӵ���������
		});
	// �����ӵ����ƶ�����;��룬��ִ�ж�������
	Vec2 MovetoPosition = pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(pAtkTarget->getPosition());
	GetSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / mySpeed, MovetoPosition), Animate::create(pAnimation), deadActionCF, NULL));
}

