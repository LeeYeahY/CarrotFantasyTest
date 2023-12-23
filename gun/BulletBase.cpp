#include "BulletBase.h"
#include "BulletManager.h"
#include "VictimEntityBase.h"
const static std::string PHOTOPOSTFIX = ".png";

BulletBase* BulletBase::Create(const int& Id, VictimEntityBase* VictimEntity)
{
	auto Bullet = new BulletBase();
	if (Bullet && Bullet->Init(Id, VictimEntity)) Bullet->autorelease();
	else CC_SAFE_DELETE(Bullet);
	return Bullet;
}

bool BulletBase::Init(const int& _Id, VictimEntityBase* VictimEntity)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Entity::Initiate(Id, BULLETCSVFILE));
		CC_BREAK_IF(!DynamicPropertyInterFace::Init(_Id, BULLETCSVFILE));

		myAtkState = CsvUtil::GetInstance()->GetInt(Id, en_AtkState, BULLETCSVFILE);//��CSV�ļ��л�ȡ������AtkState����
		myBulletType = CsvUtil::GetInstance()->GetInt(Id, en_BulletType, BULLETCSVFILE);// ��CSV�ļ��л�ȡ������BulletType����
		myDeadActCount = CsvUtil::GetInstance()->GetInt(Id, en_DeadActCount, BULLETCSVFILE);// ��CSV�ļ��л�ȡ������DeadActCount����
		CC_SAFE_RETAIN(VictimEntity);
		pAtkTarget = VictimEntity;//// ����Ŀ��ʵ����������
		IdMap = new std::set<int>();
		BulletManager::getInstance()->AddBullet(this);// ��BulletBaseʵ����ӵ�BulletManager

		bRet = true;
	} while (0);

	return  bRet;
}

void BulletBase::DoAction(const float& rDt)
{
	switch (myBulletType)
	{
	case en_NormalBullet:
	case en_GunBullet:
	{
		std::vector<std::string> AnimationFiles;// // ���������ļ�·���б�
		for (int i = 1; i <= AnimationFrameCount; ++i)//
			AnimationFiles.push_back(ModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX);//
		//// ���������ö���
		CreateDynamicEntityAnimation(AnimationFiles);
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ModelName + "1" + PHOTOPOSTFIX));
		pAnimation->setDelayPerUnit(rDt);
		GetSprite()->runAction(Animate::create(pAnimation));//// ���Ŷ���
		break;
	}
	case en_NoDisspper:
	{
		GetSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));// ��0.7����ٶȲ�����ת
		break;
	}
	default:
		break;
	}
}

void BulletBase::DoMove() {
	if (pAtkTarget->getIsDead()) // �������Ŀ���Ѿ��������Ƴ��ӵ�������Ϊ����״̬
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	DoAction(0.2f);// ִ���ӵ��Ķ�������0.2����ӳ�

	auto deadActionCF = CallFunc::create([=]()///����һ���������У������ƶ�����������
		{
			if (myBulletType == en_NormalBullet || myBulletType == en_GunBullet || myBulletType == en_StarBullet) {
				if (pAtkTarget != nullptr && !pAtkTarget->getIsDead())// �������Ŀ�������δ��������Ŀ������˺�
					pAtkTarget->Hurt(GetAtkProperty());
				this->setPosition(pAtkTarget->getPosition());//// �����ӵ�λ��Ϊ����Ŀ���λ��
			}
			DeadMove(Name);//// ִ����������
		});

	Vec2 MovetoPosition;//// �����ƶ�λ�ú;��룬�����ӵ����Ͳ�ͬ���ò�ͬ�ļ��㷽ʽ
	float MoveDistance;
	switch (myBulletType)
	{
	case en_NormalBullet:
	case en_GunBullet:
		MovetoPosition = pAtkTarget->getPosition() - this->getPosition(); //������ӵ���ǰλ��ָ�򹥻�Ŀ��λ�õ�����
		MoveDistance = this->getPosition().distance(pAtkTarget->getPosition()); //�����ӵ���ǰλ���빥��Ŀ��λ�õľ���
		break;
	case en_NoDisspper:
	{
		float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
		MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));//����һ��������ָ������Ļ����Ϊԭ�㡢�ӵ���ǰ��ת�Ƕ�Ϊ�����λ��
		MoveDistance = MovetoPosition.distance(this->getPosition());
		break;
	}
	default:
		break;
	}
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / mySpeed, MovetoPosition), deadActionCF, NULL));//// ִ���ƶ���������������
}

AtkProperty BulletBase::GetAtkProperty()
{
	AtkProperty myAtkProperty;
	myAtkProperty._enAtkState = myAtkState;
	myAtkProperty.Atk = getMyAtk();
	myAtkProperty.Duration = CsvUtil::GetInstance()->GetInt(Id, en_Duration, BULLETCSVFILE);//
	myAtkProperty.ButtltType = myBulletType;
	return myAtkProperty;
}

void BulletBase::DeadMove(const std::string& DeadImageFile)
{
	delete(IdMap);
	Entity::DeadMove(DeadImageFile);//
}

std::set<int>& BulletBase::GetIdMap()
{
	return *IdMap;
}
