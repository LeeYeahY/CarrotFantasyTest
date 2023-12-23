#include "BulletPin.h"
#include "VictimEntityBase.h"

bool BulletPin::Init(const int& Id, VictimEntityBase* VictimEntity)
{
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!BulletBase::Init(Id, VictimEntity));

		Ret = true;
	} while (0);
	return Ret;
}

BulletPin* BulletPin::Create(const int& Id, VictimEntityBase* VictimEntity)
{
	BulletPin* pBullet = new BulletPin();
	if (pBullet && pBullet->Init(Id, VictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletPin::DoAction()
{

	for (int i = 1; i <= AnimationFrameCount; ++i)//���λ�ȡ�����ӵ�������ÿһ֡
	{
		std::string SpriteFrameName = ModelName + StringUtils::format("%d.png", i);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName));
	}
	pAnimation->setDelayPerUnit(0.05);//ÿһ֡�Ĳ���ʱ����Ϊ 0.05 ��
	pAnimation->setLoops(-1);//����ѭ��
	GetSprite()->runAction(Animate::create(pAnimation));
}

void BulletPin::DoMove() {

	if (pAtkTarget->getIsDead())//��鹥��Ŀ���Ƿ��Ѿ�����
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	DoAction();

	auto deadActionCF = CallFunc::create([=]()//�����ӵ�����Ŀ���
		{

			if (pAtkTarget != nullptr && !pAtkTarget->getIsDead())
				pAtkTarget->Hurt(GetAtkProperty());
			DeadMove(Name);

		});

	float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());//������Ļ�Խ��ߵĳ���
	Vec2 MovetoPosition = pAtkTarget->getPosition() - this->getPosition();//�����ӵ��ƶ��ķ�������
	float MoveDistance = this->getPosition().distance(pAtkTarget->getPosition());//�����ӵ���Ҫ�ƶ��ľ���
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / mySpeed, MovetoPosition), deadActionCF, NULL));
}