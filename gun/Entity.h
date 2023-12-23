#pragma once
#ifndef _Enity_
#define _Enity_

#include "PublicDefine.h"
//东西类
class Entity:public Node//cocos中Node的子类
{
public:
	~Entity();//析构函数
	static int ID;//结点编号（表示当前结点编到第几号了）
	int GetMyNo();//获取结点编号

	//对实体进行初始化，Csv为保存数据的文件
	virtual bool Initiate(int ID, const std::string& CsvFileName);//根据数据对实体进行初始化的函数
	virtual const Size& GetSize()const;
	virtual void Dead()final;
	virtual void BindSprite(Sprite* Target);
	virtual Sprite* GetSprite();
	virtual Rect GetBoundingBox()const;
protected:
	virtual void DeadMove(const std::string& DeadImageFile="");
	virtual void InitiateProperty(const int MyId, const std::string& CsvFileName);

	CC_SYNTHESIZE_PASS_BY_REF(int, Id, Id);//提供设置和访问某些变量的接口函数
	CC_SYNTHESIZE_PASS_BY_REF(std::string, Name, Name); //Enity的名字
	CC_SYNTHESIZE_PASS_BY_REF(std::string, ModelName, ModelName);//Enity的类型名
	CC_SYNTHESIZE_PASS_BY_REF(int, Value, Value); //Enity的价值（如防御塔的价格和怪物的收益）
	CC_SYNTHESIZE_PASS_BY_REF(bool, IsDead, IsDead);//Enity是否死亡的标志
	CC_SYNTHESIZE_PASS_BY_REF(int, AnimationFrameCount, AnimationFrameCount);
	CC_SYNTHESIZE_PASS_BY_REF(int, Grade, Grade);//Enity等级
private:
	Sprite* MySprite;//指向精灵的指针
	static int MyNo;//记录当前结点的编号
};
#endif _Enity_