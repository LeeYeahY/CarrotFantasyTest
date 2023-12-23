#include"Entity.h"

int Entity::ID = 0;//��ʼ�������
Entity::~Entity()
{
	CC_SAFE_RELEASE_NULL(MySprite);//��ָ�����ָ����а�ȫ�ͷ�
}
bool Entity::Initiate(int ID, const std::string& CsvFileName)//�����ļ����Ƽ�����Ŷ�������г�ʼ��
{
	InitiateProperty(ID, CsvFileName);//���ݽ���ų�ʼ������ĲƲ�
	++ID;//Enity�ı�ź���һλ
	MyNo = ID;
	return true;//���س�ʼ���ɹ��ı�־
}
const Size& Entity::GetSize()const
{
	return MySprite->getContentSize();//��ȡ�ý���ԭʼ�ߴ�
}
int Entity::GetMyNo()//��ȡ��ǰ���ı��
{
	return MyNo;
}
void Entity::InitiateProperty(const int MyId, const std::string& CsvFileName)
{
	auto MyCsvUtil = CsvUtil::GetInstance();//��ȡһ��ʵ��
	Id = MyId;//�ô���Ĳ����Ը�ʵ��ı�Ž��г�ʼ��
	auto Data = MyCsvUtil->GetSomeRow(Id, CsvFileName);//�������ļ��ж�ȡ��Ӧʵ��������
	Name = Data.at(NAME);//�ֱ���ȡ�����֡����͡���ֵ�йص��ַ���
	ModelName = Data.at(MODELNAME);
	Value = atoi(Data.at(VALUE).c_str());//����ʾ��ֵ���ַ���ת��Ϊ�����洢��Value��
	AnimationFrameCount = MyCsvUtil->GetInt(Id,ANIMATION_COUNT, CsvFileName);//��ʼ���������
	Grade = MyCsvUtil->GetInt(Id, GRADE, CsvFileName);//��ʼ��ʵ��ȼ�
	IsDead = false;//��������־Ϊfalse

	std::string SpriteName = "";//Ĭ�Ͼ��������Ϊ��
	if (AnimationFrameCount) //���������ܳ�ʼΪ
		SpriteName = ModelName + "1" + PHOTOPOSTFIX;//���޸ĸþ����Ӧ��ͼƬ
	else 
		SpriteName = ModelName + PHOTOPOSTFIX;

	BindSprite(Sprite::createWithSpriteFrameName(SpriteName));//����ʵ��ľ���ָ����ͼƬ��
}
void Entity::BindSprite(cocos2d::Sprite* NewSprite)
{
	//���ȼ���Ƿ��Ѿ�ָ��ĳ��ʵ�����
	if (MySprite)//�������ͼƬ��Ϊ��
	{
		MySprite->stopAllActions();//ֹͣһ�ж���
		removeChild(MySprite);//�Ƴ���Ӧ�ĺ��ӽ��
	}
	CC_SAFE_RELEASE_NULL(MySprite);//��ȫ�ͷ�ԭ�е�ָ��
	MySprite = NewSprite;//���µľ���
	CC_SAFE_RETAIN(MySprite);//����þ�������ü�������֤�䲻�����ⲿ���ͷ�
	addChild(MySprite);//��Ӻ��ӽ��
}
Sprite* Entity::GetSprite()
{
	return MySprite;//��ȡ��ǰʵ���Ӧ����Ľӿں���
}
void Entity::Dead()
{
	//������Ϣ֪ͨ�����߽�Ǯ�仯��ǰ��Ϊ��Ϣ���ݣ�����ΪҪ���ݵĶ���
	NOTIFY->postNotification("MoneyChange", static_cast<Ref*>(&Value));
	setIsDead(true);//���ı���Ƿ������ı���
	MySprite->stopAllActions();//ʹ��ǰ����ֹͣһ�л
	DeadMove();//���������Ķ���
}
void Entity::DeadMove(const std::string& DeadImageFile)
{

	auto MyDeadImageFile = DeadImageFile;//��ʼ������ͼ��
	auto MyAnimation = Animation::create();//�����յĶ���
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//��ȡ����֡����������ڼ��غ͹�����֡

	if (!MyDeadImageFile.empty())//����ͼ��Ϊ��
	{
		switch (Grade) {//���ݵ�ǰ�ȼ���������ͼ�������
		case 1:
			MyDeadImageFile = "air0";
			break;
		case 2:
			MyDeadImageFile = "air1";
			break;
		case 3:
			MyDeadImageFile = "air2";
			break;
		}
		for (int i = 0; i < AnimationFrameCount; i++)//���ɰ�����Ӧ֡���Ķ���������ÿһ֡����֡��ӵ�������
			MyAnimation->addSpriteFrame(SpriteFrameCache->getSpriteFrameByName(MyDeadImageFile + PHOTOPOSTFIX));
		//getSpriteFrameByName()�������ֻ�ȡ����֡
		//addSpriteFrame()������֡��ӵ�������

	}
	else//����ֱ�������������֡
	{
		for (int i = 0; i < 2; i++)
			Animation->addSpriteFrame(SpriteFrameCache->getSpriteFrameByName(MyDeadImageFile + PHOTOPOSTFIX));
	}
	//���ö�������
	MyAnimation->setLoops(1);//����һ��
	MyAnimation->setDelayPerUnit(0.1f);//ÿһ֡���ӳ�Ϊ0.1s
	//ִ��һ���������У����������Ŷ����͵��ûص�������ΪLambdas���ʽ������ǰ���Ӹ��ڵ����Ƴ���
	MySprite->runAction(Sequence::create(Animate::create(MyAnimation), CallFunc::create([this]() {this->removeFromParent(); }), NULL));
}

Rect Entity::GetBoundingBox()const//��ȡ����İ�Χ��
{
	auto Pos = getPosition();//��ȡ���λ��
	auto Size = MySprite->getContentSize();//��ȡ���ԭʼ�ߴ�

	return Rect(Pos.x - Size.width / 2, Pos.y - Size.height / 2, Size.width, Size.height);
}

