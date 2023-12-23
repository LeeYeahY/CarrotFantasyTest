#include "BulletRocket.h"
#include "VictimEntityBase.h"

bool BulletRocket::Init(const int& Id, VictimEntityBase* VictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::Init(Id, VictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletRocket* BulletRocket::Create(const int& Id, VictimEntityBase* VictimEntity)
{
	BulletRocket* pBullet = new BulletRocket();
	if (pBullet && pBullet->Init(Id, VictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletRocket::DoAction()
{

	for (int i = 1; i <= AnimationFrameCount; ++i)//��ȡ����ӵ���ÿһ֡ͼƬ
	{
		std::string SpriteFrameName = ModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.05);//���ö���ÿһ֡�Ĳ��ż��ʱ��Ϊ 0.05 ��
	pAnimation->setLoops(-1);//����ѭ��
	GetSprite()->runAction(Animate::create(pAnimation));
}

void BulletRocket::DoMove() {
	if (pAtkTarget->getIsDead())//��鱻����Ŀ���Ƿ�������
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	DoAction();

	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());//������Ļ�Խ��ߵĳ���
	Vec2 MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));//���ݻ���ӵ���ǰ����ת�Ƕȣ������ӵ��ƶ���Ŀ��λ�ã������ݽǶȼ���λ������
	float MoveDistance = MovetoPosition.distance(this->getPosition());//�����ӵ���ǰλ�õ�Ŀ��λ�õľ���

	this->runAction(MoveBy::create(MoveDistance / mySpeed, MovetoPosition));
}