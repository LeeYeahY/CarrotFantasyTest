#include "Carrot.h"
#include "time.h"
#include "MapUtil.h"
#include "MonsterBase.h"
#include "MonsterManager.h"
#include "GameManager.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
Carrot::~Carrot()
{
	NOTIFY->removeAllObservers(this);
}

bool Carrot::Init()
{
	bool ret = false;

	do
	{
		CC_BREAK_IF(!Entity::Initiate(18, MONSTERCSVFILE));

		myHp = 10;//���ú��ܲ��ĳ�ʼѪ��Ϊ 10��

		GameManager::getInstance()->setMyCarrotHp(myHp);//������Ϸ�������еĺ��ܲ�Ѫ������
		auto tPoints = MapUtil::getInstance()->getMovePoses();//��ȡ�ƶ�·���������
		GetSprite()->setAnchorPoint(Vec2(0.5, 0));//���ú��ܲ������ê��
		this->setPosition((*(tPoints.end() - 2)).x + getContentSize().width / 2 - 20, (*(tPoints.end() - 2)).y - getContentSize().height / 2);//���ú��ܲ��ĳ�ʼλ��
		HpSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossHP10.png"));//������ʾѪ���ľ���
		HpSprite->setPosition(*(tPoints.end() - 1) - *(tPoints.end() - 2) + Vec2(-20, 10));//Ѫ�������λ��
		addChild(HpSprite);

		NOTIFY->addObserver(this, callfuncO_selector(Carrot::CarrotBeHurt), "CarrotHurt", nullptr);//ע��۲���,���� "CarrotHurt"
		RegisterCarrotTouchEvent();//ע������ܲ���صĴ����¼�

		srand(time(0));
		schedule(schedule_selector(Carrot::DoAction), 6);//���� DoAction��ÿ�� 6 ��ִ��һ��

		ret = true;
	} while (0);

	return  ret;
}

void Carrot::RegisterCarrotTouchEvent()
{
	auto pTouchEvent = EventListenerTouchOneByOne::create();//����һ�����㴥���¼�������

	pTouchEvent->onTouchBegan = [=](Touch* t, Event* e)//��������ʼʱ
		{
			if (getBoundingBox().containsPoint(t->getLocation())) {//����������ں��ܲ��ı߽����
				auto pCarrot = GetSprite();
				pCarrot->stopAllActions();
				pCarrot->setRotation(0);
				pCarrot->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(ModelName + PHOTOPOSTFIX)->getTexture());//���ú��ܲ����������Ϊ����״̬������
				pCarrot->runAction(DoShakeOrBlink(10, 9));//���ж�������˸�Ķ���
			}
			return false;
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, GetSprite());//��������������ӵ�����ͼ���ȼ��У��󶨵����ܲ�������
}

ActionInterval* Carrot::DoShakeOrBlink(int ImageFirstNumber, int ImageCount)
{
	auto cache = SpriteFrameCache::getInstance();
	Animation* pAnimation = Animation::create();
	std::string sSpriteFrameName;
	for (int i = ImageFirstNumber; i < ImageFirstNumber + ImageCount; i++)//// ѭ�����ָ����Χ�ڵľ���֡��������
	{
		std::string sSpriteFrameName = Name + StringUtils::format("%2d.png", i);
		pAnimation->addSpriteFrame(cache->getSpriteFrameByName(sSpriteFrameName));
	}
	pAnimation->addSpriteFrame(cache->getSpriteFrameByName(ModelName + PHOTOPOSTFIX));//// ������һ֡��������ʾ����״̬
	// ���ö����Ĳ��ż����ѭ������
	pAnimation->setDelayPerUnit(0.1);
	pAnimation->setLoops(1);
	Animate* pAnimate = Animate::create(pAnimation);
	return pAnimate;
}

void Carrot::DoAction(float t)
{
	GetSprite()->stopAllActions();
	int tRandom = rand() % 3;
	switch (tRandom)
	{
	case 0: GetSprite()->runAction(DoShakeOrBlink(10, 9));
		break;
	case 1: GetSprite()->runAction(DoShakeOrBlink(21, 3));
		break;
	case 2: GetSprite()->runAction(Sequence::create(RotateBy::create(0.2, -20), RotateBy::create(0.2, 20), RotateBy::create(0.2, 30), RotateBy::create(0.2, -30), NULL));//// ִ��һϵ����ת������ʹ���ܲ������ڶ�Ч��
		break;
	default:
		break;
	}
	SoundUtil::getInstance()->PlayEffect(StringUtils::format(CARROT, tRandom + 1));
}

void Carrot::CarrotBeHurt(Ref* pRef)
{
	SoundUtil::getInstance()->PlayEffect(CARROTCRASH);// ����������Ч
	MonsterBase* pMonster = (MonsterBase*)pRef;// �������ָ��ת��Ϊ�������
	myHp -= pMonster->getMyAtk();// ��ȥ����Ĺ�����ֵ
	if (myHp <= 0)// ����ܲ�����ֵС�ڵ���0����ʾ��Ϸʧ��
	{
		GameManager::getInstance()->setMyCarrotHp(0);
		auto tGameEndType = en_GameLose;
		NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tGameEndType));
		NOTIFY->removeAllObservers(this);// �Ƴ��������ܲ���صĹ۲���
		return;
	}
	GameManager::getInstance()->setMyCarrotHp(myHp);// �����ܲ�����ֵ
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(GetSprite());// �Ƴ��ܲ��Ĵ����¼������������ж�ʱ��
	unscheduleAllSelectors();
	HpSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("BossHP%02d.png", myHp)));// �����ܲ�����ֵ��ʾ
	std::string HurtSpriteName;
	// ���ݵ�ǰ����ֵѡ��ͬ������ͼƬ
	if (myHp == 5 || myHp == 7)
	{
		HurtSpriteName = StringUtils::format("hlb%d.png", myHp + 1);
	}
	else
	{
		HurtSpriteName = StringUtils::format("hlb%d.png", myHp);
	}
	GetSprite()->stopAllActions();// ֹͣ���ж���������������ͼƬ
	GetSprite()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(HurtSpriteName));
}

Rect Carrot::GetBoundingBox()const
{
	return Rect(getPositionX() - getContentSize().width / 2, getPositionY(), getContentSize().width, getContentSize().height);
}