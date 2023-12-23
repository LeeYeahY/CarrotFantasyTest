#include "OptLayer.h"
#include "MapUtil.h"
#include "TowerManager.h"
#include "TowerBase.h"
#include "BarrierBase.h"
#include "BarrierManager.h"
#include "TowerOpt.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"
#include "Carrot.h"
#include "GameScene.h"

bool OptLayer::Initiate()
{
	bool Ret = false;

	do
	{
		CC_BREAK_IF(!Layer::init());
		TowerOptBtn = TowerOptButton::create();//����
		TowerOptBtn->setName("TowerOptBtn");//�޸�����
		TowerOptBtn->setTag(0);//���ñ�ǩ
		ForbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png"));//��ͼƬ����һ������
		ForbiddenSp->setVisible(false);//���ò��ɼ�
		addChild(ForbiddenSp);//��ӵ���ǰͼ��
		addChild(TowerOptBtn);
		Listener();
		Ret = true;
	} while (0);

	return Ret;
}

void OptLayer::Listener()
{
	auto Listen = EventListenerTouchOneByOne::create();//���������¼��ļ�����
	Listen->onTouchBegan = [=](Touch* t, Event* e) {//���ô���ʱ�Ļص�����
		auto Pos = t->getLocation();//��ȡ�������λ��

		if (Pos.y > 590)//��Ļ�Ϸ�����
			return true;//ֱ�ӷ���true
		if (TowerOptBtn->getTag()) {//�����ǩ��0��˵����λ�õ�ǰ���ɷ��÷�����
			TowerOptBtn->setTag(0);
			TowerOptBtn->HideTowerOpt();//��������ť
		}
		else {
			//��ȡ��ǰ���еĳ�������ȡCarrot
			Carrot* MyCarrot = static_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();
			//������������ܲ��ı߽����
			if (Carrot->GetBoundingBox().containsPoint(t->getLocation())) {
				return true;//����true
			}
			//����Ƿ�����ĳ����
			for (auto& TowerItem : TowerManager::getInstance()->GetTowerVec()) {
				if (TowerItem->GetBoundingBox().containsPoint(t->getLocation())) {
					TowerOptBtn->setTag(1);//��������ť�ı�ǩ
					TowerOptBtn->setPosition(TowerItem->getPosition());//���ð�ťλ��
					TowerOptBtn->ShowTowerOpt();//��ʾ��ť
					TowerOptBtn->gradeTowerMenu(TowerItem);//��ʾ�������İ�ť
					return true;
				}
			}
			//����Ƿ��ڿհ�����
			for (auto& BlankItem : MapUtil::getInstance()->getEffectTowerPoses()) {
				if (BlankItem.containsPoint(t->getLocation())) {
					TowerOptBtn->setTag(1);
					TowerOptBtn->setPosition(BlankItem.origin + BlankItem.size / 2);
					TowerOptBtn->ShowTowerOpt();//��������ʾ�����������Ĳ˵�
					TowerOptBtn->ShowCreateMenu();
					return true;
				}

			}
			//����Ƿ���ĳ������ı߽����
			auto MonsterVec = MonsterManager::getInstance()->getMonsterVec();
			for (auto& MonsterIter : MonsterVec)
			{
				if (MonsterIter->GetBoundingBox().containsPoint(t->getLocation()))
				{
					auto MonsterLockFlag = MonsterIter->getAtkTarget();
					BarrierManager::getInstance()->ClearBeAtkLockState();//����������ϰ���ı�����״̬
					MonsterManager::getInstance()->ClearBeAtkLockState();
					MonsterIter->setAtkTarget(!MonsterLockFlag);//���ù�����Ϊ����Ŀ��
					return true;
				}
			}
			//����Ƿ���ĳ���ϰ���ı߽����
			auto BarrierVec = BarrierManager::getInstance()->GetBarrierVec();
			for (auto& BarrierItem : BarrierVec)
			{
				if (BarrierItem->GetBoundingBox().containsPoint(t->getLocation()))
				{
					auto BarrierLockFlag = BarrierItem->getAtkTarget();
					MonsterManager::getInstance()->ClearBeAtkLockState();//��չ���ı�����״̬
					BarrierManager::getInstance()->ClearBeAtkLockState();
					BarrierItem->setAtkTarget(!BarrierLockFlag);//�����ϰ�����Ϊ������״̬
					return true;
				}
			}
			SoundUtil::getInstance()->PlayEffect(SELECTFAULT);//����ѡ��������Ч
			ForbiddenSp->setVisible(true);//��Ϊ���ɼ�
			ForbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));//ִ���ȵ���󵭳��Ķ���
			ForbiddenSp->setPosition(t->getLocation());
		}
		return true;
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Listen, this);
	//��ȡ���ݵ��¼��ַ�����������������ӽ�ȥ
}
