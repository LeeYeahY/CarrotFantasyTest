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
		CC_BREAK_IF(!Entity::Initiate(Id, TOWERCSVFILE));//�����ʼ��ʵ��ʧ�ܣ���ֱ���˳�ѭ��������false

		InitTower();//��ʼ����

		TowerManager::getInstance()->AddTower(this);

		schedule(schedule_selector(Tower::CheckTarget), 0.1f);//ʹ�õ��Ⱥ�����ÿ0.1s���һ�ι���Ŀ��

		schedule(schedule_selector(Tower::Attack), AttackSpace);//ִ�й���

		schedule(schedule_selector(Tower::Rotate), 0.1f);//ִ����ת

		Ret = true;
	} while (0);

	return  Ret;
}
void Tower::InitTower()
{
	if (MyTower) //��������������ʵ��
		removeChild(MyTower);//����ʵ�����Ƴ�
	CC_SAFE_RELEASE_NULL(MyTower);//�ͷ�ָ��ʵ���ָ��

	auto CsvUtil = CsvUtil::GetInstance();//��ȡʵ��
	BulletId = CsvUtil->GetInt(Id, BULLET_ID, TOWERCSVFILE);
	AttackRange = CsvUtil->GetInt(Id, RANGE, TOWERCSVFILE);
	AttackSpace = CsvUtil->GetDouble(Id, SPACE, TOWERCSVFILE);
	UpCost = CsvUtil->GetText(Id, UP_COST, TOWERCSVFILE);
	IsRotate = CsvUtil->GetInt(Id, IS_ROTATE, TOWERCSVFILE);
	AttackUp = 0;//������ǿĿǰΪ0
	CreateCost = CsvUtil->GetInt(Id, CREATE_COST, TOWERCSVFILE);
	HaveTarget = false;

	Grade = Sprite::create();//����������ʾ����ͼ��
	Grade->setVisible(false);//��ʼ����Ϊ���ɼ�
	auto GradeAnimation = Animation::create();//������ʾ�����Ķ���
	for (int i = 1; i <= 2; i++) //������ͼ����ӵ�����֡��
		GradeAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));//��ʾ��֡����
	GradeAnimation->setDelayPerUnit(0.5);//���ö���������ʱΪ0.5s
	GradeAnimation->setLoops(1);//���ö���ѭ���Ĵ���Ϊ1
	Grade->setZOrder(3);//���ý����Ⱦ��˳��Ϊ3
	Grade->runAction(Animate::create(GradeAnimation));//����
	Grade->setPosition(0, 50);//������ʾ��λ��
	addChild(Grade);//���÷������Ϊ�½��

	MyTower = Sprite::createWithSpriteFrameName(CsvUtil->GetText(Id, TOWER_BASE, TOWERCSVFILE));
	MyTower->retain();//����Ref counting��ȷ���䲻�����ͷź�����
	MyTower->setZOrder(1);//��Ⱦ˳��
	addChild(MyTower);//��ӽ��
	GetSprite()->setZOrder(2);//���þ������Ⱦ˳��
}
void Tower::DeadMove(const std::string& DeadImageFile)
{
	NOTIFY->postNotification("TowerDead", this);//���۲��߷���Ϣ
	Entity::DeadMove(DeadImageFile);//ִ�л������������ٶ���
}
void Tower::CheckTarget(float Delta) {
	if (!Target)//�����ǰĿ��Ϊ��
		ChooseTarget();//ѡ��Ŀ��
	else {
		//���Ŀ���Ѿ����ˣ�������Ŀ�굫Ŀ�겻�Ǳ������Ķ���
		if (Target->getIsDead() || (!Target->getAtkTarget() && HaveTarget))
		{
			MissTarget();//�Ź����Ŀ��
			setHaveTarget(false);//��Ϊ��Ŀ��״̬
			return;//ֱ�ӷ���
		}
		CheckTargetIsOutOfRange();//����з���Ҫ��Ĺ���Ŀ�꣨û������������Ŀ�꣩�������Ŀ���Ƿ��ڹ�����Χ�ڲ������Ƿ񹥻�
	}
}
void Tower::ChooseTarget()
{
	//��ȡ��ǰ�洢�����vector
	auto MonsterVec = MonsterManager::getInstance()->getMonsterVec();

	for (auto& IterMonster : MonsterVec)//�������vector�е����й���
	{
		if (IsInAttackRange(IterMonster->getPosition()))//�����λ�ڹ�����Χ�ڵ�
		{
			SetTarget(IterMonster);//������Ϊ����Ŀ��
			break;//�˳�ѭ��
		}
		//�������Ѱ�ҷ��������Ĺ���
	}
}
bool Tower::IsInAttackRange(const cocos2d::Vec2& Pos) {

	bool Ret = false;

	do
	{
		auto Distance = getPosition().distance(Pos);//����distance������ȡ��ǰ�����βν���ľ���
		auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", AttackRange) + PHOTOPOSTFIX));//����һ����ʾ��Χ�ľ���
		CC_BREAK_IF(!(Distance < RangeSp->getContentSize().width / 2 + 30));//�����Χ��������false
		Ret = true;//���򷵻�true
	} while (0);

	return Ret;
}
void Tower::Attack(float Delta) {
	if (!Target || Target->getIsDead()) //�����������Ϊ�ջ��Ѿ�����
		return;//ֱ�ӷ��ؼ���
	AttackMove();//ִ�й����Ķ���

	auto CreateBulletCF = CallFunc::create([=]() {
		if (!Target)//���Ŀ��λ�գ�ֱ�ӷ���
			return;
		BulletFactory::CreateBullet(BulletId, this, Target);//���򴴽��ӵ�
		});//�����ص�����������ΪLambdas���ʽ

	this->runAction(Sequence::create(DelayTime::create(0.15), CreateBulletCF, nullptr));
	//�����������У����а������ӳ�0.15s�͵��ûص�����
}
void Tower::CheckTargetIsOutOfRange()
{
	if (Target)//�����Ŀ��
		if (!IsInAttackRange(Target->getPosition()))//���Ҽ���Ŀ���λ���Ƿ��ڹ�����Χ�ڵĽ��Ϊ���� 
			MissTarget();//��Ź����Ŀ��
}
void Tower::MissTarget() {
	CC_SAFE_RELEASE_NULL(Target);//ֱ���ͷ�Targetָ��
}
void Tower::SetTarget(VictimEntityBase* VictimEntity) {

	CC_SAFE_RELEASE_NULL(Target);//�ͷ�ԭ��Ŀ��
	Target =VictimEntity;//�滻Ϊ��Ŀ��
	CC_SAFE_RETAIN(Target);//����Ŀ����뵽���ü�������
}
Tower* Tower::PlaceTower(const int Id) {

	auto NewTower = new Tower();//�½�һ�����Ķ���

	if (NewTower && NewTower->Initiate(Id)) {//���·�������ָ�벻Ϊ���ҳ�ʼ���ɹ�
		NewTower->autorelease();//����������Զ��ͷųأ������ü�������Ϊ0ʱ�Զ��ͷţ�
		return NewTower;//�����·�������ָ��
	}

	CC_SAFE_DELETE(NewTower);//ɾ���·�������ȷ����ΪNULL
	return nullptr;//���ؿ�ָ��
}

void Tower::Rotate(float Delta) {

	if (!Target) 
		return;//������Ŀ��Ϊ�գ��򲻽�����ת

	if (IsRotate)//���������������Խ�����ת
		getSprite()->runAction(RotateTo::create(0.1, 90 - 180 * (Target->getPosition() - this->getPosition()).getAngle() / M_PI));
	//����һ����ת��������ת��ʱ��Ϊ0.1s���Ƕ��ɷ������͹����λ����ã���ִ�и���ת����
}

void Tower::AttackMove() {
	std::string SoundName = Name;//��ʼ����Ч�ļ�������
	if (SoundName == "BStar") 
		SoundName = "PStar";
	SoundUtil::getInstance()->PlayEffect(StringUtils::format("Music/Towers/%s.mp3", SoundName.c_str()));//������Ч
	auto MyAnimation = Animation::create();//��������
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//��ȡȫ�ֵľ���֡
	for (int i = 1; i <= this->getAnimationFrameCount(); i++)//��Ӷ���
		MyAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(ModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));
	MyAnimation->addSpriteFrame(MySpriteFrameCache->getSpriteFrameByName(ModelName + "1" + PHOTOPOSTFIX));//�ν�
	MyAnimation->setDelayPerUnit(0.05);//������ʱ
	MyAnimation->setLoops(1);//���Ŵ���

	auto MyAnimate = Animate::create(MyAnimation);//����������ʵ��

	this->getSprite()->runAction(MyAnimate);//ִ�в��Ŷ����Ķ���
}

void Tower::GradeUp() {
	std::stringstream StoI;
	StoI << UpCost;//��UpCostתΪ���������뵽StoI��
	int UpGradeMoney;
	StoI >> UpGradeMoney;//�����������UpGradeMoney��
	UpGradeMoney = -UpGradeMoney;//����������ǻ�Ǯ�Ĳ���
	NotificationCenter::getInstance()->postNotification("moneyChange", (Ref*)(&UpGradeMoney));//֪ͨ�������ֽ�Ǯ�ı仯

	auto UpGradeCounts = this->getAttackUp();
	Grade->removeFromParentAndCleanup(true);//�Ƴ�������־�Ľ�㲢������Դ
	GetSprite()->removeFromParentAndCleanup(true);//�Ƴ���ǰ���Ľ��
	Entity::InitiateProperty(this->getId() + 1, TOWERCSVFILE);//��һ���µ�

	InitTower();//��ʼ��������
	this->AttackUp = UpGradeCounts;//����ԭ�е�����������������һ������
}

int Tower::GetUpCost() {
	std::stringstream StoI;
	StoI << UpCost;//�������Ļ������ַ���תΪ����
	int UpGradeMoney;
	StoI >> UpGradeMoney;
	return UpGradeMoney;//����
}

void Tower::ShowGrade() {
	Grade->setVisible(true);//���õȼ�����Ϊ�ɼ�
}
void Tower::HideGrade() {
	Grade->setVisible(false);//���õȼ�����Ϊ���ɼ�
}