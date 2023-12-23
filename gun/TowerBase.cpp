#include"Tower.h"
#include "TowerManager.h"
#include "VictimEntityBase.h"
#include "CsvUtil.h"
#include "BulletBase.h"
#include "BulletFactory.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"

Tower::~Tower()
{
	CC_SAFE_RELEASE_NULL(Target);
	CC_SAFE_RELEASE_NULL(MyTower);
}
bool Tower::Initiate(const int Id) {

	bool Ret = false;

	do {
		CC_BREAK_IF(!Entity::Initiate(Id, TOWERCSVFILE));//如果初始化实体失败，则直接退出循环，返回false

		InitTower();//初始化塔

		TowerManager::getInstance()->AddTower(this);

		schedule(schedule_selector(Tower::CheckTarget), 0.1f);//使用调度函数，每0.1s检查一次攻击目标

		schedule(schedule_selector(Tower::Attack), AttackSpace);//执行攻击

		schedule(schedule_selector(Tower::Rotate), 0.1f);//执行旋转

		Ret = true;
	} while (0);

	return  Ret;
}
void Tower::InitTower()
{
	if (MyTower) //如果这个塔已有有实体
		removeChild(MyTower);//将该实体结点移除
	CC_SAFE_RELEASE_NULL(MyTower);//释放指向实体的指针

	auto CsvUtil = CsvUtil::GetInstance();//获取实例
	BulletId = CsvUtil->GetInt(Id, BULLET_ID, TOWERCSVFILE);
	AttackRange = CsvUtil->GetInt(Id, RANGE, TOWERCSVFILE);
	AttackSpace = CsvUtil->GetDouble(Id, SPACE, TOWERCSVFILE);
	UpCost = CsvUtil->GetText(Id, UP_COST, TOWERCSVFILE);
	IsRotate = CsvUtil->GetInt(Id, IS_ROTATE, TOWERCSVFILE);
	AttackUp = 0;//属性增强目前为0
	CreateCost = CsvUtil->GetInt(Id, CREATE_COST, TOWERCSVFILE);
	HaveTarget = false;

	Grade = Sprite::create();//创建精灵显示升级图标
	Grade->setVisible(false);//初始设置为不可见
	auto GradeAnimation = Animation::create();//创建显示升级的动画
	for (int i = 1; i <= 2; i++) //将升级图像添加到精灵帧中
		GradeAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));//显示两帧动画
	GradeAnimation->setDelayPerUnit(0.5);//设置动画播放延时为0.5s
	GradeAnimation->setLoops(1);//设置动画循环的次数为1
	Grade->setZOrder(3);//设置结点渲染的顺序为3
	Grade->runAction(Animate::create(GradeAnimation));//播放
	Grade->setPosition(0, 50);//设置显示的位置
	addChild(Grade);//将该分数添加为新结点

	MyTower = Sprite::createWithSpriteFrameName(CsvUtil->GetText(Id, TOWER_BASE, TOWERCSVFILE));
	MyTower->retain();//增加Ref counting，确保其不会在释放后被销毁
	MyTower->setZOrder(1);//渲染顺序
	addChild(MyTower);//添加结点
	GetSprite()->setZOrder(2);//设置精灵的渲染顺序
}
void Tower::DeadMove(const std::string& DeadImageFile)
{
	NOTIFY->postNotification("TowerDead", this);//给观察者发信息
	Entity::DeadMove(DeadImageFile);//执行基类中塔的销毁动作
}
void Tower::CheckTarget(float Delta) {
	if (!Target)//如果当前目标为空
		ChooseTarget();//选择目标
	else {
		//如果目标已经死了，或者有目标但目标不是被锁定的对象
		if (Target->getIsDead() || (!Target->getAtkTarget() && HaveTarget))
		{
			MissTarget();//放过这个目标
			setHaveTarget(false);//置为无目标状态
			return;//直接返回
		}
		CheckTargetIsOutOfRange();//如果有符合要求的攻击目标（没死而且是锁定目标），则检查该目标是否在攻击范围内并决定是否攻击
	}
}
void Tower::ChooseTarget()
{
	//获取当前存储怪物的vector
	auto MonsterVec = MonsterManager::getInstance()->getMonsterVec();

	for (auto& IterMonster : MonsterVec)//遍历这个vector中的所有怪物
	{
		if (IsInAttackRange(IterMonster->getPosition()))//如果有位于攻击范围内的
		{
			SetTarget(IterMonster);//则将其设为攻击目标
			break;//退出循环
		}
		//否则继续寻找符合条件的怪物
	}
}
bool Tower::IsInAttackRange(const cocos2d::Vec2& Pos) {

	bool Ret = false;

	do
	{
		auto Distance = getPosition().distance(Pos);//调用distance函数获取当前结点和形参结点间的距离
		auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", AttackRange) + PHOTOPOSTFIX));//创建一个表示范围的精灵
		CC_BREAK_IF(!(Distance < RangeSp->getContentSize().width / 2 + 30));//如果范围不合理返回false
		Ret = true;//否则返回true
	} while (0);

	return Ret;
}
void Tower::Attack(float Delta) {
	if (!Target || Target->getIsDead()) //如果攻击对象为空或已经死了
		return;//直接返回即可
	AttackMove();//执行攻击的动作

	auto CreateBulletCF = CallFunc::create([=]() {
		if (!Target)//如果目标位空，直接返回
			return;
		BulletFactory::CreateBullet(BulletId, this, Target);//否则创建子弹
		});//创建回调函数，参数为Lambdas表达式

	this->runAction(Sequence::create(DelayTime::create(0.15), CreateBulletCF, nullptr));
	//创建动作序列，其中包括：延迟0.15s和调用回调函数
}
void Tower::CheckTargetIsOutOfRange()
{
	if (Target)//如果有目标
		if (!IsInAttackRange(Target->getPosition()))//而且检查该目标的位置是否在攻击范围内的结果为不在 
			MissTarget();//则放过这个目标
}
void Tower::MissTarget() {
	CC_SAFE_RELEASE_NULL(Target);//直接释放Target指针
}
void Tower::SetTarget(VictimEntityBase* VictimEntity) {

	CC_SAFE_RELEASE_NULL(Target);//释放原有目标
	Target =VictimEntity;//替换为新目标
	CC_SAFE_RETAIN(Target);//将新目标加入到引用计数当中
}
Tower* Tower::PlaceTower(const int Id) {

	auto NewTower = new Tower();//新建一个塔的对象

	if (NewTower && NewTower->Initiate(Id)) {//若新防御塔的指针不为空且初始化成功
		NewTower->autorelease();//将对象加入自动释放池（当引用计数被减为0时自动释放）
		return NewTower;//返回新防御塔的指针
	}

	CC_SAFE_DELETE(NewTower);//删除新防御塔，确保其为NULL
	return nullptr;//返回空指针
}

void Tower::Rotate(float Delta) {

	if (!Target) 
		return;//若攻击目标为空，则不进行旋转

	if (IsRotate)//如果这个防御塔可以进行旋转
		getSprite()->runAction(RotateTo::create(0.1, 90 - 180 * (Target->getPosition() - this->getPosition()).getAngle() / M_PI));
	//创建一个旋转，其中旋转的时间为0.1s，角度由防御塔和怪物的位置算得，并执行该旋转动作
}

void Tower::AttackMove() {
	std::string SoundName = Name;//初始化音效文件的名字
	if (SoundName == "BStar") 
		SoundName = "PStar";
	SoundUtil::getInstance()->PlayEffect(StringUtils::format("Music/Towers/%s.mp3", SoundName.c_str()));//播放音效
	auto MyAnimation = Animation::create();//创建动画
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//获取全局的精灵帧
	for (int i = 1; i <= this->getAnimationFrameCount(); i++)//添加动画
		MyAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(ModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));
	MyAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(ModelName + "1" + PHOTOPOSTFIX));//衔接
	MyAnimation->setDelayPerUnit(0.05);//设置延时
	MyAnimation->setLoops(1);//播放次数

	auto MyAnimate = Animate::create(MyAnimation);//创建动作的实例

	this->getSprite()->runAction(MyAnimate);//执行播放动画的动作
}

void Tower::GradeUp() {
	std::stringstream StoI;
	StoI << UpCost;//将UpCost转为整数并读入到StoI中
	int UpGradeMoney;
	StoI >> UpGradeMoney;//将整数输出到UpGradeMoney中
	UpGradeMoney = -UpGradeMoney;//购买防御塔是花钱的操作
	NotificationCenter::getInstance()->postNotification("moneyChange", (Ref*)(&UpGradeMoney));//通知其他部分金钱的变化

	auto UpGradeCounts = this->getAttackUp();
	Grade->removeFromParentAndCleanup(true);//移除升级标志的结点并清理资源
	GetSprite()->removeFromParentAndCleanup(true);//移除当前塔的结点
	Entity::InitiateProperty(this->getId() + 1, TOWERCSVFILE);//换一个新滴

	InitTower();//初始化防御塔
	this->AttackUp = UpGradeCounts;//保留原有的升级次数，便于下一次升级
}

int Tower::GetUpCost() {
	std::stringstream StoI;
	StoI << UpCost;//将升级的花费由字符串转为整数
	int UpGradeMoney;
	StoI >> UpGradeMoney;
	return UpGradeMoney;//返回
}

void Tower::ShowGrade() {
	Grade->setVisible(true);//设置等级精灵为可见
}
void Tower::HideGrade() {
	Grade->setVisible(false);//设置等级精灵为不可见
}