#include"Entity.h"

int Entity::ID = 0;//初始化结点编号
Entity::~Entity()
{
	CC_SAFE_RELEASE_NULL(MySprite);//对指向精灵的指针进行安全释放
}
bool Entity::Initiate(int ID, const std::string& CsvFileName)//根据文件名称及结点编号对物体进行初始化
{
	InitiateProperty(ID, CsvFileName);//根据结点编号初始化物体的财产
	++ID;//Enity的编号后移一位
	MyNo = ID;
	return true;//返回初始化成功的标志
}
const Size& Entity::GetSize()const
{
	return MySprite->getContentSize();//获取该结点的原始尺寸
}
int Entity::GetMyNo()//获取当前结点的编号
{
	return MyNo;
}
void Entity::InitiateProperty(const int MyId, const std::string& CsvFileName)
{
	auto MyCsvUtil = CsvUtil::GetInstance();//获取一个实例
	Id = MyId;//用传入的参数对该实体的编号进行初始化
	auto Data = MyCsvUtil->GetSomeRow(Id, CsvFileName);//从数据文件中读取对应实例的数据
	Name = Data.at(NAME);//分别提取与名字、类型、价值有关的字符串
	ModelName = Data.at(MODELNAME);
	Value = atoi(Data.at(VALUE).c_str());//将表示价值的字符串转换为整数存储到Value中
	AnimationFrameCount = MyCsvUtil->GetInt(Id,ANIMATION_COUNT, CsvFileName);//初始化动画框架
	Grade = MyCsvUtil->GetInt(Id, GRADE, CsvFileName);//初始化实体等级
	IsDead = false;//置死亡标志为false

	std::string SpriteName = "";//默认精灵的名字为空
	if (AnimationFrameCount) //如果动画框架初始为
		SpriteName = ModelName + "1" + PHOTOPOSTFIX;//则修改该精灵对应的图片
	else 
		SpriteName = ModelName + PHOTOPOSTFIX;

	BindSprite(Sprite::createWithSpriteFrameName(SpriteName));//将该实体的精灵指针与图片绑定
}
void Entity::BindSprite(cocos2d::Sprite* NewSprite)
{
	//首先检查是否已经指向某个实体对象
	if (MySprite)//如果精灵图片不为空
	{
		MySprite->stopAllActions();//停止一切动作
		removeChild(MySprite);//移除对应的孩子结点
	}
	CC_SAFE_RELEASE_NULL(MySprite);//安全释放原有的指针
	MySprite = NewSprite;//绑定新的精灵
	CC_SAFE_RETAIN(MySprite);//加入该精灵的引用计数，保证其不会在外部被释放
	addChild(MySprite);//添加孩子结点
}
Sprite* Entity::GetSprite()
{
	return MySprite;//读取当前实体对应精灵的接口函数
}
void Entity::Dead()
{
	//发送消息通知监听者金钱变化，前者为消息内容，后者为要传递的东西
	NOTIFY->postNotification("MoneyChange", static_cast<Ref*>(&Value));
	setIsDead(true);//更改标记是否死亡的变量
	MySprite->stopAllActions();//使当前精灵停止一切活动
	DeadMove();//做出死亡的动作
}
void Entity::DeadMove(const std::string& DeadImageFile)
{

	auto MyDeadImageFile = DeadImageFile;//初始化死亡图像
	auto MyAnimation = Animation::create();//创建空的动画
	auto MySpriteFrameCache = SpriteFrameCache::getInstance();//获取精灵帧缓存对象，用于加载和管理精灵帧

	if (!MyDeadImageFile.empty())//死亡图像为空
	{
		switch (Grade) {//根据当前等级更改死亡图像的名字
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
		for (int i = 0; i < AnimationFrameCount; i++)//生成包含对应帧数的动画，并将每一帧精灵帧添加到动画中
			MyAnimation->addSpriteFrame(SpriteFrameCache->getSpriteFrameByName(MyDeadImageFile + PHOTOPOSTFIX));
		//getSpriteFrameByName()根据名字获取精灵帧
		//addSpriteFrame()将精灵帧添加到动画中

	}
	else//否则直接添加两个精灵帧
	{
		for (int i = 0; i < 2; i++)
			Animation->addSpriteFrame(SpriteFrameCache->getSpriteFrameByName(MyDeadImageFile + PHOTOPOSTFIX));
	}
	//设置动画属性
	MyAnimation->setLoops(1);//播放一次
	MyAnimation->setDelayPerUnit(0.1f);//每一帧的延迟为0.1s
	//执行一个动作序列，包括：播放动画和调用回调函数（为Lambdas表达式，将当前结点从父节点中移除）
	MySprite->runAction(Sequence::create(Animate::create(MyAnimation), CallFunc::create([this]() {this->removeFromParent(); }), NULL));
}

Rect Entity::GetBoundingBox()const//获取精灵的包围盒
{
	auto Pos = getPosition();//获取结点位置
	auto Size = MySprite->getContentSize();//获取结点原始尺寸

	return Rect(Pos.x - Size.width / 2, Pos.y - Size.height / 2, Size.width, Size.height);
}

