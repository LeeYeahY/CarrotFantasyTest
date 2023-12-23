#include "TowerOpt.h"
#include "PublicSourceDefine.h"
#include "MapUtil.h"
#include "TowerFactory.h"
#include "LevelConfigUtil.h"
#include "ScoreAndControlLayer.h"
#include "Tower.h"
#include "SoundUtil.h"

TowerOptButton::TowerOptButton()
{
	;
}

TowerOptButton::~TowerOptButton()
{
	CC_SAFE_DELETE(CreateTowerItemSpVec);
	CC_SAFE_DELETE(GradeTowerItemSpVec);
}

bool TowerOptButton::Initiate()
{
	CreateTowerItemSpVec = new Vector<MenuItemSprite*>();
	GradeTowerItemSpVec = new Vector<MenuItemSprite*>();
	CreateMenuAndItems();
	this->schedule(schedule_selector(TowerOptButton::ChangeItem));
}

void TowerOptButton::HideTowerOpt()
{
	KeySpVisible = false;//按键设置为不可见
	KeySp->setVisible(KeySpVisible);
	if (TowerRangeSp != nullptr) //如果塔的范围不为空
		TowerRangeSp->setVisible(false);//设为不可见
	CreateMenu->setVisible(false);//创建菜单设为不可见
}

void TowerOptButton::ShowTowerOpt() 
{
	KeySpVisible = true;//设置按键为可见
	KeySp->setVisible(KeySpVisible);
}

void TowerOptButton::CreateMenuAndItems() {
	KeySp = Sprite::create();//创建按键精灵
	KeySp->setVisible(false);//设置为不可见
	CreateMenu = Menu::create();//创建菜单
	CreateMenu->setVisible(false);
	GradeMenu = Menu::create();//创建等级菜单
	CreateTowerMenu();//创建防御塔菜单
	auto MenuAnimation = Animation::create();//菜单动画
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//获取全局精灵帧
	for (int i = 1; i <= 4; ++i)//将菜单的图片添加到动画中
		MenuAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(StringUtils::format("select_0%d", i) + PHOTOPOSTFIX));
	MenuAnimation->setDelayPerUnit(0.1);//设置延时
	MenuAnimation->setLoops(-1);//播放次数

	KeySp->runAction(Animate::create(MenuAnimation));//先执行播放动画的操作
	KeySp->addChild(CreateMenu);//添加塔的菜单到Key的孩子结点中
	KeySp->addChild(GradeMenu);//添加等级菜单
	addChild(KeySp);//添加KeySp到当前结点的孩子结点中（通过控制KeySp的可见性来显示或隐藏相关元素）

	TowerRangeSp = Sprite::create();//创建塔的攻击的精灵
	TowerRangeSp->setPosition(40, 40);//设置初始位置
	TowerRangeSp->setVisible(false);//设为不可见
	KeySp->addChild(TowerRangeSp);//添加到Key的孩子结点中
}

void TowerOptButton::CreateTowerMenu() {
	//遍历塔
	for (auto& IterTower : LevelConfigUtil::getInstance()->GetCurLevelTowersInfo()) {
		int TowerId = CsvUtil::GetInstance()->FindValueWithLine(IterTower, 1, TOWERCSVFILE);//获取塔的ID
		std::stringstream StoI;
		std::string UpgradeCost = CsvUtil::GetInstance()->GetText(TowerId, CREATE_COST, TOWERCSVFILE);//将塔升级的金额转换为整数
		StoI << UpgradeCost;
		int UpGradeMoney;
		StoI >> UpGradeMoney;
		if (IterTower == "Sun1") 
			IterTower = "Sun";
		auto TowerItemSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(IterTower + "01" + PHOTOPOSTFIX));//将塔的图片创建为精灵
		auto TowerItem = MenuItemSprite::create(TowerItemSp, TowerItemSp, [=](Ref* r) {//创建菜单精灵，包含两个状态：正常和选中，最后是在用户选择时执行的操作
			TowerType MyTowerType;
			this->setTag(0);
			HideTowerOpt();//隐藏塔的选项
			if (UpGradeMoney > CheckMoney()) {//如果花费的金额大于现有金币，直接返回
				return;
			}
			switch (TowerId)//检查读取到的塔的编号
			{
				//根据不同的塔的编号初始化塔的类型
			case 13:
				MyTowerType = STAR_TOWER; 
				break;
			case 28:
				MyTowerType = PIN_TOWER; 
				break;
			case 25:
				MyTowerType = ROCKET_TOWER; 
				break;
			default:
				break;
			}
			//用塔的类型创建对应的防御塔
			TowerFactory::CreateTower(MyTowerType, this->getPosition());
			SoundUtil::getInstance()->PlayEffect(BUILDTOWER);//播放建造防御塔的音效
			int CreateMoney = -CsvUtil::GetInstance()->GetInt(TowerId, CREATE_COST, TOWERCSVFILE);//获取塔的造价
			NotificationCenter::getInstance()->PostNotification("MoneyChange", (Ref*)(&CreateMoney));//给监管者发消息
			});
		TowerItem->setTag(UpGradeMoney);//设置菜单精灵的标签为花费的金额
		TowerItem->setName(IterTower);//设置菜单精灵的名字
		CreateTowerItemSpVec->pushBack(TowerItem);//将这个防御塔放入UI元素的容器中
		CreateMenu->addChild(TowerItem);//添加到菜单中
	}
	CreateMenu->AlignItemsHorizontallyWithPadding(1);//水平排列菜单选项并指定间距为1
}

void TowerOptButton::GradeTowerMenu(Tower* TouchTower) {
	GradeMenu->removeAllChildrenWithCleanup(true);
	auto SpriteFrameCache = SpriteFrameCache::getInstance();
	TowerRangeSp->setSpriteFrame(SpriteFrameCache->getSpriteFrameByName("range_" + StringUtils::format("%d", TouchTower->getAttackRange()) + PHOTOPOSTFIX));
	TowerRangeSp->setVisible(true);
	auto AtkRange = Sprite::createWithSpriteFrame(SpriteFrameCache->getSpriteFrameByName(StringUtils::format("range_%d", TouchTower->getAttackRange()) + PHOTOPOSTFIX));
	auto UpgradeSp = Sprite::createWithSpriteFrame(SpriteFrameCache->getSpriteFrameByName("upgrade_" + TouchTower->getUpCost() + PHOTOPOSTFIX));
	auto UpgradeItem = MenuItemSprite::create(UpgradeSp, UpgradeSp, [=](Ref* r) {
		this->setTag(0);
		HideTowerOpt();
		if (TouchTower->getAttackUp() > 1)
			return;
		if (TouchTower->GetUpCost() > CheckMoney()) 
			return;
	    TouchTower->GradeUp();
		SoundUtil::getInstance()->PlayEffect(UPGRADETOWER);
		TouchTower->setAttackUp(TouchTower->getAttackUp() + 1);
		});
	auto SellSp = Sprite::createWithSpriteFrame(SpriteFrameCache->getSpriteFrameByName(StringUtils::format("sell_%d", TouchTower->getValue()) + PHOTOPOSTFIX));
	auto SellItem = MenuItemSprite::create(SellSp, SellSp, [=](Ref* r) {
		this->setTag(0);
		HideTowerOpt();
		SoundUtil::getInstance()->PlayEffect(SELLTOWER);
		TouchTower->Dead();
		});

	UpgradeItem->setName("upgrade_");
	UpgradeItem->setTag(TouchTower->GetUpCost());
	GradeTowerItemSpVec->pushBack(UpgradeItem);
	GradeMenu->addChild(UpgradeItem);
	GradeMenu->addChild(SellItem);
	if (this->getPositionY() >= 480) {
		if (this->getPositionX() < 80) 
			UpgradeItem->setPosition(Vec2(80, 0));
		else 
			UpgradeItem->setPosition(Vec2(-80, 0));
		SellItem->setPosition(Vec2(0, -80));
	}
	else if (this->getPositionY() < 80) {
		if (this->getPositionX() < 80) 
			SellItem->setPosition(Vec2(80, 0));
		else 
			SellItem->setPosition(Vec2(-80, 0));
		UpgradeItem->setPosition(Vec2(0, 80));
	}
	else 
		GradeMenu->alignItemsVerticallyWithPadding(100);//设置间隔
	GradeMenu->setPosition(40, 40);//显示位置
}

void TowerOptButton::ChangeItem(float Delta) {
	for (auto ItemCreateSp = CreateTowerItemSpVec->begin(); ItemCreateSp != CreateTowerItemSpVec->end(); ItemCreateSp++) {
		auto CreateItemSp = (*ItemCreateSp);//遍历创建塔的菜单的UI容器
		if (CreateItemSp->getTag() > CheckMoney()) //如果某一个按键的Tag大于当前金币数量
			CreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(CreateItemSp->getName() + "00" + PHOTOPOSTFIX)));//设置它的正常显示图像
		else 
			CreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(CreateItemSp->getName() + "01" + PHOTOPOSTFIX)));
	}
	for (auto ItemGradeSp = GradeTowerItemSpVec->begin(); ItemGradeSp != GradeTowerItemSpVec->end(); ItemGradeSp++) {
		auto GradeItemSp = (*ItemGradeSp);//遍历存储等级菜单的UI容器
		if (GradeItemSp->getTag() != 0) {
			if (GradeItemSp->getTag() > CheckMoney()) 
				GradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(GradeItemSp->getName() + StringUtils::format("%d", -GradeItemSp->getTag()) + PHOTOPOSTFIX)));
			else 
				GradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(GradeItemSp->getName() + StringUtils::format("%d", GradeItemSp->getTag()) + PHOTOPOSTFIX)));
		}
	}
}

void TowerOptButton::SetFuncCheckMoney(const std::function<int()>& FuncCheckMoney) {
	CheckMoney = FuncCheckMoney;
}

void TowerOptButton::ShowMenu() {
	GradeMenu->removeAllChildrenWithCleanup(true);//清空所有子结点
	CreateMenu->setVisible(true);//设置创建防御塔的菜单为可见
	if (this->getPositionY() < 320)
		CreateMenu->setPosition(40, 120);
	else
		CreateMenu->setPosition(40, -50);
	int x1 = 120;
	int x2 = 120;
	switch (CreateTowerItemSpVec->size())//存储创建防御塔的元素的UI容器
	{
	case 1:
		x1 = 0; 
		break;
	case 2:
		x1 = 40; 
		break;
	case 3:
		x1 = 80; 
		break;
	default:
		break;
	}
	if (this->getPositionX() <= 120)
		CreateMenu->setPosition(CreateMenu->getPosition() + Vec2(x1, 0));
	if (this->getPositionX() >= 840)
		CreateMenu->setPosition(CreateMenu->getPosition() + Vec2(-x1, 0));
}

void TowerOptButton::HideMenu() {
	CreateMenu->setVisible(false);
}