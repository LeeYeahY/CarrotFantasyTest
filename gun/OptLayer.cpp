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
		TowerOptBtn = TowerOptButton::create();//创建
		TowerOptBtn->setName("TowerOptBtn");//修改名字
		TowerOptBtn->setTag(0);//设置标签
		ForbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png"));//用图片创建一个精灵
		ForbiddenSp->setVisible(false);//设置不可见
		addChild(ForbiddenSp);//添加到当前图层
		addChild(TowerOptBtn);
		Listener();
		Ret = true;
	} while (0);

	return Ret;
}

void OptLayer::Listener()
{
	auto Listen = EventListenerTouchOneByOne::create();//创建触摸事件的监听器
	Listen->onTouchBegan = [=](Touch* t, Event* e) {//设置触摸时的回调函数
		auto Pos = t->getLocation();//获取触摸点的位置

		if (Pos.y > 590)//屏幕上方区域
			return true;//直接返回true
		if (TowerOptBtn->getTag()) {//如果标签非0，说明该位置当前不可放置防御塔
			TowerOptBtn->setTag(0);
			TowerOptBtn->HideTowerOpt();//隐藏塔按钮
		}
		else {
			//获取当前运行的场景并获取Carrot
			Carrot* MyCarrot = static_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();
			//如果触摸点在萝卜的边界框里
			if (Carrot->GetBoundingBox().containsPoint(t->getLocation())) {
				return true;//返回true
			}
			//检查是否触摸到某个塔
			for (auto& TowerItem : TowerManager::getInstance()->GetTowerVec()) {
				if (TowerItem->GetBoundingBox().containsPoint(t->getLocation())) {
					TowerOptBtn->setTag(1);//设置塔按钮的标签
					TowerOptBtn->setPosition(TowerItem->getPosition());//设置按钮位置
					TowerOptBtn->ShowTowerOpt();//显示按钮
					TowerOptBtn->gradeTowerMenu(TowerItem);//显示塔升级的按钮
					return true;
				}
			}
			//检查是否在空白区域
			for (auto& BlankItem : MapUtil::getInstance()->getEffectTowerPoses()) {
				if (BlankItem.containsPoint(t->getLocation())) {
					TowerOptBtn->setTag(1);
					TowerOptBtn->setPosition(BlankItem.origin + BlankItem.size / 2);
					TowerOptBtn->ShowTowerOpt();//若是则显示创建防御塔的菜单
					TowerOptBtn->ShowCreateMenu();
					return true;
				}

			}
			//检查是否在某个怪物的边界框内
			auto MonsterVec = MonsterManager::getInstance()->getMonsterVec();
			for (auto& MonsterIter : MonsterVec)
			{
				if (MonsterIter->GetBoundingBox().containsPoint(t->getLocation()))
				{
					auto MonsterLockFlag = MonsterIter->getAtkTarget();
					BarrierManager::getInstance()->ClearBeAtkLockState();//若是则清空障碍物的被攻击状态
					MonsterManager::getInstance()->ClearBeAtkLockState();
					MonsterIter->setAtkTarget(!MonsterLockFlag);//将该怪物设为攻击目标
					return true;
				}
			}
			//检查是否在某个障碍物的边界框内
			auto BarrierVec = BarrierManager::getInstance()->GetBarrierVec();
			for (auto& BarrierItem : BarrierVec)
			{
				if (BarrierItem->GetBoundingBox().containsPoint(t->getLocation()))
				{
					auto BarrierLockFlag = BarrierItem->getAtkTarget();
					MonsterManager::getInstance()->ClearBeAtkLockState();//清空怪物的被攻击状态
					BarrierManager::getInstance()->ClearBeAtkLockState();
					BarrierItem->setAtkTarget(!BarrierLockFlag);//将该障碍物设为被攻击状态
					return true;
				}
			}
			SoundUtil::getInstance()->PlayEffect(SELECTFAULT);//播放选择错误的音效
			ForbiddenSp->setVisible(true);//设为不可见
			ForbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));//执行先淡入后淡出的动作
			ForbiddenSp->setPosition(t->getLocation());
		}
		return true;
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Listen, this);
	//获取导演的事件分发器，并将监听器添加进去
}
