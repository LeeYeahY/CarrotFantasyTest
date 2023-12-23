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
	KeySpVisible = false;//��������Ϊ���ɼ�
	KeySp->setVisible(KeySpVisible);
	if (TowerRangeSp != nullptr) //������ķ�Χ��Ϊ��
		TowerRangeSp->setVisible(false);//��Ϊ���ɼ�
	CreateMenu->setVisible(false);//�����˵���Ϊ���ɼ�
}

void TowerOptButton::ShowTowerOpt() 
{
	KeySpVisible = true;//���ð���Ϊ�ɼ�
	KeySp->setVisible(KeySpVisible);
}

void TowerOptButton::CreateMenuAndItems() {
	KeySp = Sprite::create();//������������
	KeySp->setVisible(false);//����Ϊ���ɼ�
	CreateMenu = Menu::create();//�����˵�
	CreateMenu->setVisible(false);
	GradeMenu = Menu::create();//�����ȼ��˵�
	CreateTowerMenu();//�����������˵�
	auto MenuAnimation = Animation::create();//�˵�����
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//��ȡȫ�־���֡
	for (int i = 1; i <= 4; ++i)//���˵���ͼƬ��ӵ�������
		MenuAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(StringUtils::format("select_0%d", i) + PHOTOPOSTFIX));
	MenuAnimation->setDelayPerUnit(0.1);//������ʱ
	MenuAnimation->setLoops(-1);//���Ŵ���

	KeySp->runAction(Animate::create(MenuAnimation));//��ִ�в��Ŷ����Ĳ���
	KeySp->addChild(CreateMenu);//������Ĳ˵���Key�ĺ��ӽ����
	KeySp->addChild(GradeMenu);//��ӵȼ��˵�
	addChild(KeySp);//���KeySp����ǰ���ĺ��ӽ���У�ͨ������KeySp�Ŀɼ�������ʾ���������Ԫ�أ�

	TowerRangeSp = Sprite::create();//�������Ĺ����ľ���
	TowerRangeSp->setPosition(40, 40);//���ó�ʼλ��
	TowerRangeSp->setVisible(false);//��Ϊ���ɼ�
	KeySp->addChild(TowerRangeSp);//��ӵ�Key�ĺ��ӽ����
}

void TowerOptButton::CreateTowerMenu() {
	//������
	for (auto& IterTower : LevelConfigUtil::getInstance()->GetCurLevelTowersInfo()) {
		int TowerId = CsvUtil::GetInstance()->FindValueWithLine(IterTower, 1, TOWERCSVFILE);//��ȡ����ID
		std::stringstream StoI;
		std::string UpgradeCost = CsvUtil::GetInstance()->GetText(TowerId, CREATE_COST, TOWERCSVFILE);//���������Ľ��ת��Ϊ����
		StoI << UpgradeCost;
		int UpGradeMoney;
		StoI >> UpGradeMoney;
		if (IterTower == "Sun1") 
			IterTower = "Sun";
		auto TowerItemSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(IterTower + "01" + PHOTOPOSTFIX));//������ͼƬ����Ϊ����
		auto TowerItem = MenuItemSprite::create(TowerItemSp, TowerItemSp, [=](Ref* r) {//�����˵����飬��������״̬��������ѡ�У���������û�ѡ��ʱִ�еĲ���
			TowerType MyTowerType;
			this->setTag(0);
			HideTowerOpt();//��������ѡ��
			if (UpGradeMoney > CheckMoney()) {//������ѵĽ��������н�ң�ֱ�ӷ���
				return;
			}
			switch (TowerId)//����ȡ�������ı��
			{
				//���ݲ�ͬ�����ı�ų�ʼ����������
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
			//���������ʹ�����Ӧ�ķ�����
			TowerFactory::CreateTower(MyTowerType, this->getPosition());
			SoundUtil::getInstance()->PlayEffect(BUILDTOWER);//���Ž������������Ч
			int CreateMoney = -CsvUtil::GetInstance()->GetInt(TowerId, CREATE_COST, TOWERCSVFILE);//��ȡ�������
			NotificationCenter::getInstance()->PostNotification("MoneyChange", (Ref*)(&CreateMoney));//������߷���Ϣ
			});
		TowerItem->setTag(UpGradeMoney);//���ò˵�����ı�ǩΪ���ѵĽ��
		TowerItem->setName(IterTower);//���ò˵����������
		CreateTowerItemSpVec->pushBack(TowerItem);//���������������UIԪ�ص�������
		CreateMenu->addChild(TowerItem);//��ӵ��˵���
	}
	CreateMenu->AlignItemsHorizontallyWithPadding(1);//ˮƽ���в˵�ѡ�ָ�����Ϊ1
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
		GradeMenu->alignItemsVerticallyWithPadding(100);//���ü��
	GradeMenu->setPosition(40, 40);//��ʾλ��
}

void TowerOptButton::ChangeItem(float Delta) {
	for (auto ItemCreateSp = CreateTowerItemSpVec->begin(); ItemCreateSp != CreateTowerItemSpVec->end(); ItemCreateSp++) {
		auto CreateItemSp = (*ItemCreateSp);//�����������Ĳ˵���UI����
		if (CreateItemSp->getTag() > CheckMoney()) //���ĳһ��������Tag���ڵ�ǰ�������
			CreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(CreateItemSp->getName() + "00" + PHOTOPOSTFIX)));//��������������ʾͼ��
		else 
			CreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(CreateItemSp->getName() + "01" + PHOTOPOSTFIX)));
	}
	for (auto ItemGradeSp = GradeTowerItemSpVec->begin(); ItemGradeSp != GradeTowerItemSpVec->end(); ItemGradeSp++) {
		auto GradeItemSp = (*ItemGradeSp);//�����洢�ȼ��˵���UI����
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
	GradeMenu->removeAllChildrenWithCleanup(true);//��������ӽ��
	CreateMenu->setVisible(true);//���ô����������Ĳ˵�Ϊ�ɼ�
	if (this->getPositionY() < 320)
		CreateMenu->setPosition(40, 120);
	else
		CreateMenu->setPosition(40, -50);
	int x1 = 120;
	int x2 = 120;
	switch (CreateTowerItemSpVec->size())//�洢������������Ԫ�ص�UI����
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